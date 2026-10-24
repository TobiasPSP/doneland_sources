"""Local UI fixture server. No hardware access; commands modify a preview only."""
from http.server import BaseHTTPRequestHandler, ThreadingHTTPServer
from pathlib import Path
from urllib.parse import urlparse, parse_qs
import argparse, gzip, json, re

project = Path(__file__).resolve().parents[1]
fixtures = project / '.pio/preview'
scene = 'configure-ready'
state = json.loads((fixtures / f'{scene}.state.json').read_text())

class Handler(BaseHTTPRequestHandler):
    def log_message(self, *args):
        pass
    def send(self, data, mime='application/json', compressed=False):
        if not isinstance(data, bytes):
            data = json.dumps(data, separators=(',', ':')).encode()
        self.send_response(200)
        self.send_header('Content-Type', mime)
        self.send_header('Cache-Control', 'no-store')
        if compressed:
            self.send_header('Content-Encoding', 'gzip')
        self.send_header('Content-Length', str(len(data)))
        self.end_headers()
        self.wfile.write(data)
    def do_GET(self):
        global state, scene
        url = urlparse(self.path)
        query = parse_qs(url.query)
        if url.path == '/responsive':
            self.send(b'<!doctype html><html><head><title>390px responsive preview</title><style>body{margin:0;background:#0b0e10;display:flex;justify-content:center;padding:8px}iframe{border:0;width:390px;height:850px;max-width:100%}</style></head><body><iframe src="/?scene=charging" title="390 pixel charger dashboard"></iframe></body></html>', 'text/html; charset=utf-8')
        elif url.path == '/':
            selected = query.get('scene', [None])[0]
            if selected and re.fullmatch(r'[a-z0-9-]+', selected) and (fixtures / f'{selected}.state.json').exists():
                scene = selected
                state = json.loads((fixtures / f'{scene}.state.json').read_text())
            self.send(gzip.compress((project / 'web/index.html').read_bytes(), mtime=0), 'text/html; charset=utf-8', True)
        elif url.path == '/assets/montserrat-latin.woff2':
            self.send((project / 'web/assets/montserrat-latin.woff2').read_bytes(), 'font/woff2')
        elif url.path == '/api/state':
            self.send(state)
        elif url.path == '/api/model':
            self.send((fixtures / 'model.json').read_bytes())
        elif url.path == '/api/diagnostics':
            self.send((fixtures / f'{scene}.diagnostics.json').read_bytes())
        elif url.path == '/api/history':
            source = json.loads((fixtures / f'{scene}.history.json').read_text())
            after = int(query.get('after', ['0'])[0])
            session = int(query.get('session', ['0'])[0])
            reset = session != state['session'] or after != source['next']
            source.update(session=state['session'],reset=reset)
            if not reset:
                source.update(samples=[],modes=[])
            self.send(source)
        else:
            self.send_error(404)
    def do_POST(self):
        global state, scene
        if self.path != '/api/command':
            self.send_error(404)
            return
        values = {k: v[0] for k, v in parse_qs(self.rfile.read(int(self.headers['Content-Length'])).decode(), keep_blank_values=True).items()}
        action = values['action']
        if action == 'start':
            scene = 'charging'
            state = json.loads((fixtures / f'{scene}.state.json').read_text())
        elif action == 'abort':
            state.update(state='aborted', summary=True, message='Charge aborted', disableConfirmed=True,stop_failed=False)
        elif action == 'summary':
            state['summary'] = True
        elif action == 'configure':
            state.update(state='configure', summary=False, message='Ready')
        elif action == 'settings':
            for key in ['persist', 'wifi', 'espNow']:
                state['options'][key] = values[key] == '1'
            state['options'].update(mode=int(values['mode']), ssid=values['ssid'], hostname=values['hostname'])
        elif action == 'cancel':
            state['notice'] = ''
        state['revision'] += 1
        self.send(dict(id=int(values['id']), code=0, revision=state['revision'], message='Preview: '+action+' applied'))

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--port', type=int, default=8769)
    args = parser.parse_args()
    print(f'Fixture-only web preview at http://127.0.0.1:{args.port}/', flush=True)
    ThreadingHTTPServer(('127.0.0.1', args.port), Handler).serve_forever()

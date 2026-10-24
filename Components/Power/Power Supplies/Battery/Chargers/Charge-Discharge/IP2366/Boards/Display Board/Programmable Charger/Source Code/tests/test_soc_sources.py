"""Verify charging-reference digitization, rates, units and source hashes."""
from pathlib import Path
import hashlib
import json
import re

project = Path(__file__).resolve().parents[1]
code = (project / 'include/soc.h').read_text(encoding='utf-8')
sources = project / 'docs/sources'
references = json.loads((sources / 'charging-curves.json').read_text())
assert references['units']['voltage'] == 'mV per cell'
count = 0
for key in ['lfp', 'ion', 'hv']:
    reference = references[key]
    body = re.search(r'\b' + key + r'Curve\[\]\s*=\s*\{(.*?)\};', code, re.S).group(1)
    points = [[float(a), float(b)] for a, b in re.findall(r'\{([\d.]+)f?,\s*([\d.]+)f?\}', body)]
    assert points == reference['points'], key
    assert reference['rate_C'] == (0.5 if key == 'hv' else 1)
    assert hashlib.sha256((sources / reference['source']).read_bytes()).hexdigest() == reference['sha256']
    assert points[0][0] == 0 and points[-1][0] == 100
    assert all(a[0] < b[0] and a[1] <= b[1] for a, b in zip(points, points[1:])), key
    count += len(points)
assert references['lfp']['points'][-1][1] == 3650
assert references['ion']['points'][-1][1] == 4200
assert references['hv']['points'][-1][1] == 4400
# Historical OCV snapshots remain for provenance; they are no longer active.
for entry in (sources / 'SHA256SUMS.txt').read_text().splitlines():
    filename, expected = entry.split()
    assert hashlib.sha256((sources / filename).read_bytes()).hexdigest() == expected
print(f'PASS: {count} charging reference points, rates, explicit units and primary-source hashes')

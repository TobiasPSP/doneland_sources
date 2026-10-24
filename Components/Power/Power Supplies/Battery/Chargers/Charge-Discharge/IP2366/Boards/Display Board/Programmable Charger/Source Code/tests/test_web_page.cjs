const fs=require('fs'),vm=require('vm'),path=require('path'),assert=require('assert'),zlib=require('zlib');
const project=path.resolve(__dirname,'..'),html=fs.readFileSync(path.join(project,'web/index.html'),'utf8'),script=html.split('<script>')[1].split('</script>')[0];
const context2d=new Proxy({},{get:(o,p)=>p in o?o[p]:(()=>{})});
function element(){return {value:'',checked:false,disabled:false,hidden:false,style:{},dataset:{},children:[],classList:{toggle:()=>{}},addEventListener(name,callback){(this.listeners??={})[name]=callback},setAttribute(name,value){this[name]=value},click(){this.listeners?.click?.({preventDefault(){}})},getBoundingClientRect:()=>({width:850,height:350}),getContext:()=>context2d,replaceChildren(...items){this.children=items},append(item){this.children.push(item)},showModal(){this.open=true},close(){this.open=false}}}
const elements=new Map([...html.matchAll(/\bid="([^"]+)"/g)].map(m=>[m[1],element()]));
const choices=[...html.matchAll(/<button[^>]*data-(tab|chemistry|cells)="([^"]+)"/g)].map(m=>{const e=element();e.dataset[m[1]]=m[2];return e});
const sandbox={BATCHARGER_TEST:true,console,AbortController,URLSearchParams,Date,Math,Number,Error,Blob,Uint8Array,TextEncoder,devicePixelRatio:1,setTimeout:()=>0,clearTimeout:()=>{},addEventListener:()=>{},fetch:async()=>{throw Error('Unexpected network access')},document:{hidden:false,getElementById:id=>{assert(elements.has(id),id);return elements.get(id)},createElement:()=>element(),querySelectorAll:selector=>choices.filter(e=>e.dataset[selector.slice(6,-1)]!==undefined),addEventListener:()=>{}}};
vm.createContext(sandbox);vm.runInContext(script,sandbox);const funcs=vm.runInContext('({validConfig,target,effectiveCurrent,applyHistory,validateState,duration,socProgress})',sandbox);
const fixtures=path.join(project,'.pio/preview'),model=JSON.parse(fs.readFileSync(path.join(fixtures,'model.json')));sandbox.loadedModel=model;vm.runInContext('model=loadedModel',sandbox);
const references=JSON.parse(fs.readFileSync(path.join(project,'docs/sources/charging-curves.json')));
for(const [index,key] of [[1,'lfp'],[2,'ion'],[3,'hv']])assert.deepEqual(model.curves[index],references[key].points);
let checked=0,maxState=0,maxHistory=0;
for(const file of fs.readdirSync(fixtures).filter(f=>f.endsWith('.state.json'))){
 const raw=fs.readFileSync(path.join(fixtures,file),'utf8'),state=JSON.parse(raw);maxState=Math.max(maxState,Buffer.byteLength(raw));funcs.validateState(state);
 assert(!raw.includes('example-pass')&&!raw.includes('secret-not-for-json'));assert(!('password' in state.options));
 sandbox.fixture=state;vm.runInContext('state=fixture;draftDirty=false;settingsDirty=false;render()',sandbox);
 assert.equal(elements.get('friendlyName').value,state.options.friendlyName);
 assert.equal(Number(elements.get('voltageCalibration_mV').value),state.options.voltageCalibration_mV);assert.equal(Number(elements.get('currentCalibration_mA').value),state.options.currentCalibration_mA);
 const historyFile=file.replace('.state.json','.history.json'),historyRaw=fs.readFileSync(path.join(fixtures,historyFile),'utf8'),packet=JSON.parse(historyRaw);maxHistory=Math.max(maxHistory,Buffer.byteLength(historyRaw));
 vm.runInContext('history=[];historyCursor=0;historySession=0',sandbox);funcs.applyHistory(packet);assert.equal(vm.runInContext('history.length',sandbox),packet.samples.length);
 const unchanged=path.join(fixtures,file.replace('.state.json','.delta.json'));
 if(packet.samples.length&&fs.existsSync(unchanged)){const delta=JSON.parse(fs.readFileSync(unchanged));assert(!delta.reset&&delta.samples.length===0&&delta.modes.length===0);funcs.applyHistory(delta);assert.equal(vm.runInContext('history.length',sandbox),packet.samples.length);}
 assert.equal(elements.get('power').textContent,state.valid?`${(state.voltage_mV*state.current_mA/1000000).toFixed(2)} W`:'-- W');
 assert.equal(elements.get('sessionOwner').textContent,state.session_origin);
 if(['starting','charging'].includes(state.state))assert(!elements.get('summaryWarning').textContent.includes('disable NOT confirmed'));
 assert.equal(elements.get('socProgress').style.width,(state.valid&&Number.isFinite(state.soc_percent)?Math.round(funcs.socProgress(state.soc_percent,state.active.percent)*10)/10:0)+'%');
 if(file==='charging.state.json'){assert.equal(state.voltage_mV,12480);assert.equal(state.current_mA,640);assert.equal(state.target_mV,12600);assert.equal(state.vmin_mV,9000);assert.equal(state.vmax_mV,13600);assert.equal(state.imax_mA,1300);}
 if(file==='charging-soc-capped.state.json')assert.equal(state.soc_percent,99);
 if(file==='complete.state.json')assert.equal(state.soc_percent,100);
 if(file==='graph-full-history.state.json')assert(packet.samples.length<=300&&packet.total_samples===320);
 if(file==='graph-ten-hours.state.json'){assert.equal(packet.total_samples,36001);assert.equal(packet.duration_ms,36000000);assert(packet.samples.length<=300&&packet.samples[0][0]===0&&packet.samples.at(-1)[0]===36000000);assert.equal(packet.modes.length,5);}
 if(file==='web-command-settings.state.json'){assert.equal(state.options.ssid,'quoted"ssid\\test');assert(state.options.passwordSet&&state.options.wifi&&state.options.persist);}
 const diagnostic=JSON.parse(fs.readFileSync(path.join(fixtures,file.replace('.state.json','.diagnostics.json'))));assert(diagnostic.text.includes('BatCharger 1.7.8'));checked++;
}
for(const [chemistry,cell_mV,target_mV] of [[1,3650,3470],[2,4200,4120],[3,4400,4260]]){const config={chemistry,cells:4,percent:80,cell_mV,current_mA:2000,termination_mA:100,terminationTime_min:360};assert.equal(funcs.validConfig(config),'');assert.equal(funcs.target(config),target_mV);config.percent=100;assert.equal(funcs.target(config),cell_mV);}
assert.equal(funcs.effectiveCurrent({chemistry:3,cells:6,percent:100,cell_mV:4400,current_mA:9700,termination_mA:100,terminationTime_min:360}),3700);
assert(funcs.validConfig({chemistry:0}));assert.throws(()=>funcs.validateState({schema:99}));assert.throws(()=>funcs.applyHistory({session:1,next:1,reset:true,samples:[[NaN,0]]}));assert.throws(()=>funcs.applyHistory({session:1,next:1,reset:true,samples:Array(301).fill([1,1])}));assert.equal(funcs.duration(3661000),'01:01:01');
assert.equal(Math.round(funcs.socProgress(60,70)*10)/10,85.7);
assert.equal(funcs.socProgress(80,70),100);assert.equal(funcs.socProgress(0,0),100);
assert.equal(funcs.socProgress(NaN,70),0);
// Review is local: Cancel sends no command, and summary contains the requested values.
sandbox.reviewFixture={chemistry:1,cells:4,percent:80,cell_mV:3650,current_mA:2000,termination_mA:100,terminationTime_min:360};
vm.runInContext('draft={...reviewFixture};reviewStart()',sandbox);
assert(elements.get('startDialog').open);assert.equal(elements.get('startDetails').children[1].textContent,'14.600 V');
assert.equal(elements.get('startDetails').children.at(-1).textContent,'6 h 00 min');
elements.get('cancelStart').click();assert(!elements.get('startDialog').open);
assert.equal(vm.runInContext('startReview',sandbox),null);
assert(html.includes('--soc-green:#00ff35'));
// Local navigation preserves the stopped graph, even after returning to setup.
sandbox.completed=JSON.parse(fs.readFileSync(path.join(fixtures,'complete.state.json')));
vm.runInContext("state=completed;stoppedSummary=null;render();showTab('graph')",sandbox);
assert(!elements.get('graphTab').hidden&&!elements.get('graphCard').hidden);
assert(elements.get('chargerTab').hidden&&elements.get('summaryTab').hidden);
for(const key of ['voltage','current','temperature','elapsed','soc'])assert.equal(elements.get('graph_'+key).textContent,elements.get(key).textContent);
vm.runInContext("showTab('summary')",sandbox);
assert(!elements.get('summaryTab').hidden&&!elements.get('summaryCard').hidden);
assert(elements.get('graphTab').hidden);
const stoppedTotal=elements.get('summaryCharge').textContent;
vm.runInContext("state={...state,state:'configure',summary:false,message:'Ready'};render();showTab('graph')",sandbox);
assert(!elements.get('graphCard').hidden);
assert.equal(elements.get('summaryCharge').textContent,stoppedTotal);
assert.equal(elements.get('summaryReason').textContent,sandbox.completed.message);
vm.runInContext("state={...state,session:0};render();showTab('summary')",sandbox);
assert(elements.get('graphCard').hidden&&elements.get('summaryCard').hidden);
assert(!elements.get('graphEmpty').hidden&&!elements.get('summaryEmpty').hidden);
sandbox.charging=JSON.parse(fs.readFileSync(path.join(fixtures,'charging.state.json')));
vm.runInContext("state=charging;render()",sandbox);assert.equal(elements.get('summaryWarning').textContent,'');
vm.runInContext("state={...state,state:'fault',stop_failed:true};render()",sandbox);assert(elements.get('summaryWarning').textContent.includes('disable NOT confirmed'));
vm.runInContext("state={...state,stop_failed:false};render()",sandbox);assert(!elements.get('summaryWarning').textContent.includes('disable NOT confirmed'));
const header=fs.readFileSync(path.join(project,'include/web_page.h'),'utf8');function asset(name){const body=header.split(`${name}[] PROGMEM={`)[1].split('};')[0];return Buffer.from([...body.matchAll(/0x([\da-f]{2})/g)].map(m=>parseInt(m[1],16)))}
assert.equal(zlib.gunzipSync(asset('WebPageGzip')).toString(),html);assert.deepEqual(asset('WebFont'),fs.readFileSync(path.join(project,'web/assets/montserrat-latin.woff2')));
assert(!html.includes('/api/frame')&&!html.includes('/api/tap')&&!html.includes('decodeFrame'));assert(checked>=33&&maxState<6000&&maxHistory<16384);
console.log(`PASS: ${checked} JSON screen states, native command fixtures, full-session history/300 points, units/curves, password privacy, responsive renderer and embedded assets; max state ${maxState} bytes, history ${maxHistory} bytes`);
// Serializing includes body consumption; queue failures must not poison later requests.
(async()=>{
 sandbox.captureState=JSON.parse(fs.readFileSync(path.join(fixtures,'charging.state.json')));
 sandbox.captureHistory=JSON.parse(fs.readFileSync(path.join(fixtures,'charging.history.json')));
 vm.runInContext('state=captureState;applyHistory(captureHistory)',sandbox);
 const capture=vm.runInContext('exportCanvas()',sandbox);assert.equal(capture.width,1600);assert.equal(capture.height,1060);
 const pdf=vm.runInContext('pdfFromJpeg(new Uint8Array([255,216,255,217]),1600,1060)',sandbox);
 const bytes=Buffer.from(await pdf.arrayBuffer()),syntax=bytes.toString('latin1');
 assert.equal(pdf.type,'application/pdf');assert(syntax.startsWith('%PDF-1.4\n'));
 const xref=Number(syntax.match(/startxref\n(\d+)/)[1]);assert.equal(syntax.slice(xref,xref+4),'xref');
 const entries=syntax.slice(xref).split('\n').slice(3,8);
 entries.forEach((entry,i)=>{assert.equal(entry.length,19);const offset=Number(entry.slice(0,10));assert(syntax.slice(offset).startsWith(`${i+1} 0 obj\n`))});
 assert.throws(()=>vm.runInContext('pdfFromJpeg(new Uint8Array([0]),1,1)',sandbox),/Invalid JPEG/);
 assert(html.includes('Save as PNG')&&html.includes('Save as PDF'));
 console.log('PASS: fixed-size export capture, PDF byte offsets/xref/stream construction, invalid-capture rejection');
 const api=vm.runInContext('api',sandbox);let release,entered;
 const started=new Promise(resolve=>entered=resolve),gate=new Promise(resolve=>release=resolve),order=[];
 sandbox.fetch=async path=>{order.push(path);return {ok:true,json:async()=>{if(path==='/slow'){entered();await gate}return {path}}}};
 const first=api('/slow'),second=api('/next');await started;assert.deepEqual(order,['/slow']);release();await Promise.all([first,second]);assert.deepEqual(order,['/slow','/next']);
 let calls=0;sandbox.fetch=async()=>{if(++calls===1)throw Object.assign(Error('aborted without a reason'),{name:'AbortError'});return {ok:true,json:async()=>({ok:true})}};
 assert((await api('/read')).ok);assert.equal(calls,2);
 calls=0;sandbox.fetch=async()=>{calls++;throw Object.assign(Error('aborted without a reason'),{name:'AbortError'})};
 await assert.rejects(api('/api/command',{method:'POST'}),/Tablet request interrupted/);assert.equal(calls,1);
 calls=0;sandbox.fetch=async()=>{calls++;return {ok:false,status:409,json:async()=>({message:'Rejected'})}};
 await assert.rejects(api('/read'),/Rejected/);assert.equal(calls,1);
 sandbox.fetch=async()=>({ok:true,json:async()=>({ok:true})});assert((await api('/recovered')).ok);
 elements.get('connectionError').hidden=true;sandbox.fetch=async()=>{throw Error('Polling must pause during command')};
 await vm.runInContext('pending=true;poll()',sandbox);vm.runInContext('pending=false',sandbox);
 assert(elements.get('connectionError').hidden);
 sandbox.setTimeout=fn=>{queueMicrotask(fn);return 1};
 sandbox.fetch=async(path,{signal})=>new Promise((resolve,reject)=>signal.addEventListener('abort',()=>reject(Object.assign(Error('aborted'),{name:'AbortError'}))));
 await assert.rejects(api('/timeout'),/Tablet request timed out \(8 s\)/);
 sandbox.setTimeout=()=>0;
 console.log('PASS: one request including body at a time, interrupted GET recovery, no POST replay, no HTTP rejection retry, queue recovery');
})().catch(error=>{console.error(error);process.exitCode=1});

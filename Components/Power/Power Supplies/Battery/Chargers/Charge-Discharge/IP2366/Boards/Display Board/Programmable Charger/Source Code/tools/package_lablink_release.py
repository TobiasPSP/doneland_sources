"""Package the built charger image without uploading any device."""
from pathlib import Path
import hashlib, json, shutil, subprocess, sys
project = Path(__file__).resolve().parents[1]
python = Path.home()/".platformio/penv/Scripts/python.exe"
metadata = json.loads(subprocess.check_output([str(python),"-m","platformio","project","metadata","-d",str(project),"--json-output"],text=True))["tablet"]["extra"]
images = [(int(i["offset"],0),Path(i["path"])) for i in metadata["flash_images"]]
images.append((int(metadata["application_offset"],0), project/".pio/build/tablet/firmware.bin"))
images.sort()
out=project/"firmware"
for _, path in images: shutil.copy2(path,out/path.name)
shutil.copy2(project/".pio/build/tablet/firmware.elf",out/"firmware.elf")
tool=None
for p in (Path.home()/".platformio/packages").glob("tool-esptoolpy*/esptool.py"):
    if json.loads((p.parent/"package.json").read_text(encoding="utf-8")).get("version")=="2.40900.250804": tool=p
if tool is None: raise SystemExit("Pinned esptool missing")
merged=out/"BatCharger-combined.bin"
cmd=[str(python),str(tool),"--chip","esp32s3","merge_bin","-o",str(merged),"--flash_mode","keep","--flash_freq","keep","--flash_size","keep"]
for offset,path in images: cmd += [hex(offset),str(out/path.name)]
subprocess.run(cmd,check=True)
data=merged.read_bytes()
for offset,path in images:
    block=(out/path.name).read_bytes()
    assert data[offset:offset+len(block)]==block,path
(out/"SHA256SUMS.txt").write_text("".join(hashlib.sha256(p.read_bytes()).hexdigest()+"  "+p.name+"\n" for p in sorted(out.iterdir()) if p.is_file() and p.name!="SHA256SUMS.txt"),encoding="utf-8")
print("Verified BatCharger images; no device flashed.")

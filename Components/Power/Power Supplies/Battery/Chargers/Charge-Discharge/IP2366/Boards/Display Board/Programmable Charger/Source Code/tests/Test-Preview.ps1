[CmdletBinding()]
param([string]$Compiler='C:\Program Files\LLVM\bin\clang++.exe')
$project=Split-Path $PSScriptRoot -Parent
$lvgl=Join-Path $project '.pio\libdeps\tablet\lvgl'
$testOutput=Join-Path $project '.pio\preview'
$null=New-Item -ItemType Directory -Force -Path $testOutput
$exe=Join-Path $testOutput 'preview.exe'
$response=Join-Path $testOutput 'build.rsp'
$arguments=@('-w','-DLV_CONF_INCLUDE_SIMPLE','-DTABLET_PREVIEW')
foreach($path in @((Join-Path $project 'include'),(Join-Path $project 'lib\IP2366Control\src'),(Join-Path $project 'lib\LabLink\src'),$lvgl)){$arguments+='-I"'+$path.Replace('\','/')+'"'}
$arguments+='-x c'
foreach($file in (Get-ChildItem -LiteralPath (Join-Path $lvgl 'src') -Recurse -Filter '*.c')){$arguments+='"'+$file.FullName.Replace('\','/')+'"'}
$arguments+=@('-x c++',('"'+(Join-Path $PSScriptRoot 'preview.cpp').Replace('\','/')+'"'),'-o',('"'+$exe.Replace('\','/')+'"'))
$arguments+='"'+(Join-Path $project 'lib\IP2366Control\src\IP2366.cpp').Replace('\','/')+'"'
[IO.File]::WriteAllLines($response,[string[]]$arguments,(New-Object Text.UTF8Encoding($false)))
& $Compiler ('@'+$response)
if($LASTEXITCODE -ne 0){throw 'LVGL preview compilation failed'}
& $exe $testOutput
if($LASTEXITCODE -ne 0){throw 'LVGL UI regression failed'}
Write-Output "Previews: $testOutput"

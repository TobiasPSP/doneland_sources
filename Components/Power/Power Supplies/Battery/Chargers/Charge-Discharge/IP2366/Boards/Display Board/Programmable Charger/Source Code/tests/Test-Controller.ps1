[CmdletBinding()]
param([string]$Compiler='C:\Program Files\LLVM\bin\clang++.exe')
$project=Split-Path $PSScriptRoot -Parent
$testOutput=Join-Path $project '.pio\tests'
$null=New-Item -ItemType Directory -Force -Path $testOutput
$exe=Join-Path $testOutput 'controller.exe'
$library=Join-Path $project 'lib\IP2366Control\src'
$driver=Join-Path $library 'IP2366.cpp'
& $Compiler '-std=c++17' '-Wall' '-Wextra' '-Werror' ('-I'+(Join-Path $project 'include')) ('-I'+$library) $driver (Join-Path $PSScriptRoot 'test_controller.cpp') '-o' $exe
if($LASTEXITCODE -ne 0){throw 'Controller test compilation failed'}
& $exe
if($LASTEXITCODE -ne 0){throw 'Controller tests failed'}
$busExe=Join-Path $testOutput 'bus.exe'
& $Compiler '-std=c++17' '-Wall' '-Wextra' '-Werror' ('-I'+(Join-Path $PSScriptRoot 'stubs')) ('-I'+(Join-Path $project 'include')) ('-I'+$library) (Join-Path $PSScriptRoot 'test_bus.cpp') '-o' $busExe
if($LASTEXITCODE -ne 0){throw 'Bus test compilation failed'}
& $busExe
if($LASTEXITCODE -ne 0){throw 'Bus tests failed'}
$libraryExe=Join-Path $testOutput 'ip2366.exe'
& $Compiler '-std=c++17' '-Wall' '-Wextra' '-Werror' ('-I'+$library) $driver (Join-Path $PSScriptRoot 'test_ip2366.cpp') '-o' $libraryExe
if($LASTEXITCODE -ne 0){throw 'Standalone library test compilation failed'}
& $libraryExe
if($LASTEXITCODE -ne 0){throw 'Standalone library tests failed'}
$settingsExe=Join-Path $testOutput 'settings-web.exe'
& $Compiler '-std=c++17' '-Wall' '-Wextra' '-Werror' ('-I'+(Join-Path $PSScriptRoot 'stubs')) ('-I'+(Join-Path $project 'include')) ('-I'+$library) $driver (Join-Path $PSScriptRoot 'test_settings_web.cpp') '-o' $settingsExe
if($LASTEXITCODE -ne 0){throw 'Settings/web test compilation failed'}
& $settingsExe
if($LASTEXITCODE -ne 0){throw 'Settings/web tests failed'}

$historyExe=Join-Path $testOutput 'history.exe'
& $Compiler '-std=c++17' '-Wall' '-Wextra' '-Werror' ('-I'+(Join-Path $project 'include')) (Join-Path $PSScriptRoot 'test_history.cpp') '-o' $historyExe
if($LASTEXITCODE -ne 0){throw 'History test compilation failed'}
& $historyExe
if($LASTEXITCODE -ne 0){throw 'History tests failed'}

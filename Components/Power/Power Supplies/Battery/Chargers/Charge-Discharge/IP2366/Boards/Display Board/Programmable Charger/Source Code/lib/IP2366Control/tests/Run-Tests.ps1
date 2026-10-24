[CmdletBinding()]
param([string]$Compiler='C:\Program Files\LLVM\bin\clang++.exe')
$library=Split-Path $PSScriptRoot -Parent
$testOutput=Join-Path $library '.test-build'
$null=New-Item -ItemType Directory -Force -Path $testOutput
$exe=Join-Path $testOutput 'ip2366-tests.exe'
& $Compiler '-std=c++17' '-Wall' '-Wextra' '-Werror' ('-I'+(Join-Path $library 'src')) (Join-Path $library 'src\IP2366.cpp') (Join-Path $PSScriptRoot 'test_ip2366.cpp') '-o' $exe
if($LASTEXITCODE -ne 0){throw 'Standalone IP2366 test compilation failed'}
& $exe
if($LASTEXITCODE -ne 0){throw 'Standalone IP2366 tests failed'}

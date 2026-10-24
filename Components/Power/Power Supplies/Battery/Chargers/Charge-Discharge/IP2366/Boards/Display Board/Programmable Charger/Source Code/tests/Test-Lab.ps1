[CmdletBinding()]
param([string]$Compiler='C:\Program Files\LLVM\bin\clang++.exe')
$project=Split-Path $PSScriptRoot -Parent
$out=Join-Path $project '.pio\tests'
$null=New-Item -ItemType Directory -Force -Path $out
$lib=Join-Path $project 'lib\LabLink'
$cases=@(
    @{Name='lab-ownership';Source=(Join-Path $PSScriptRoot 'test_lab_ownership.cpp')},
    @{Name='lab-server';Source=(Join-Path $PSScriptRoot 'test_lab_server.cpp')},
    @{Name='lab-protocol';Source=(Join-Path $lib 'tests\test_lablink.cpp')},
    @{Name='lab-meter';Source=(Join-Path $lib 'tests\test_meter.cpp')}
)
foreach($case in $cases){
    $exe=Join-Path $out ($case.Name+'.exe')
    & $Compiler '-std=c++17' '-D_CRT_SECURE_NO_WARNINGS' '-Wall' '-Wextra' '-Werror' ('-I'+(Join-Path $project 'include')) ('-I'+(Join-Path $lib 'src')) $case.Source '-o' $exe
    if($LASTEXITCODE -ne 0){throw ($case.Name+' compilation failed')}
    & $exe
    if($LASTEXITCODE -ne 0){throw ($case.Name+' failed')}
}

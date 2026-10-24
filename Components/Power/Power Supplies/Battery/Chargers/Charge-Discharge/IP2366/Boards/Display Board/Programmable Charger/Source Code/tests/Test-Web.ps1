[CmdletBinding()]
param([string]$Node='node')
# First run Test-Preview.ps1 to generate fresh native screen/JSON fixtures.
& $Node (Join-Path $PSScriptRoot 'test_web_page.cjs')
if($LASTEXITCODE -ne 0){throw 'Web JSON/page regression failed'}

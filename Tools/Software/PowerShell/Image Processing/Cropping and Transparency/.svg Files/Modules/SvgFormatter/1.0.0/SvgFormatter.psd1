
@{

# Module Loader File
RootModule = 'loader.psm1'

# Version Number
ModuleVersion = '1.0.0'

# Unique Module ID
GUID = '5ec0aa9a-b6a5-4cac-8e40-b6f692d421a7'

# Module Author
Author = 'Dr. Tobias Weltner'

# Company
CompanyName = 'powershell.one'

# Copyright
Copyright = '(c) 2024 Dr. Tobias Weltner. All rights reserved.'

# Module Description
Description = 'helper functions to trim, prettify and convert svg graphics'

# Minimum PowerShell Version Required
PowerShellVersion = ''

# Name of Required PowerShell Host
PowerShellHostName = ''

# Minimum Host Version Required
PowerShellHostVersion = ''

# Minimum .NET Framework-Version
DotNetFrameworkVersion = ''

# Minimum CLR (Common Language Runtime) Version
CLRVersion = ''

# Processor Architecture Required (X86, Amd64, IA64)
ProcessorArchitecture = ''

# Required Modules (will load before this module loads)
RequiredModules = @()

# Required Assemblies
RequiredAssemblies = @()

# PowerShell Scripts (.ps1) that need to be executed before this module loads
ScriptsToProcess = @()

# Type files (.ps1xml) that need to be loaded when this module loads
TypesToProcess = @()

# Format files (.ps1xml) that need to be loaded when this module loads
FormatsToProcess = @()

# 
NestedModules = @()

# List of exportable functions
FunctionsToExport = '*'

# List of exportable cmdlets
CmdletsToExport = @('Format-Svg','Test-ImageMetadata')

# List of exportable variables
VariablesToExport = '*'

# List of exportable aliases
AliasesToExport = '*'

# List of all modules contained in this module
ModuleList = @()

# List of all files contained in this module
FileList = @()

# Private data that needs to be passed to this module
PrivateData = ''

}
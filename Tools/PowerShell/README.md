<img src="/assets/images/butler.jpg" width="80%" height="80%" />
 
# Tools

> PowerShell Is A Cross-Platform Scripting Language, And It Is Simple To Create Tools And Custom Commands


**PowerShell** surfaced in 2009 as a new modern and *object-oriented* scripting language in *Windows*. Today, it is *cross-platform* and also [available](https://github.com/PowerShell/PowerShell/releases) for *Linux*, *MacOS* and many other operating systems.

## Installing PowerShell

On *Windows*, you do not necessarily need to install **PowerShell**: *Windows PowerShell* is part of the operating system. Just press `Win`+`R` to open the *Run* dialog, then enter `powershell` and press `ENTER`.

### PowerShell 7: Cross Platform

On other operating systems (and also on *Windows* if you want to use the *latest* **PowerShell** version), visit [PowerShell Releases](https://github.com/PowerShell/PowerShell/releases). 

Scroll down until you see the item *Assets*. Click to expand.

<img src="images/powershell_assets.png" width="50%" height="50%" />

This opens a list of ready-to-download installation binaries, available for many operating systems and in many formats (*tar.gz*, *zip*, *msi*, *pkg*).

> [!CAUTION]
> Make sure you select the appropriate operating system. For *Windows*, this would be the suffix *win-x64*.

When you download an *archive* format such as *tar.gz* or *zip*, you can use **PowerShell** as a *portable app*. Here is how:

1. Download the appropriate archive file
2. *Unblock* the downloaded file *before* you unpack it: in *Windows*, right-click the downloaded archive file, choose *Properties*, then check *Unblock*.
3. Open the folder with the unpacked files, and launch `pwsh.exe`

## Getting Doneland PowerShell Tools

**PowerShell** comes with a basic set of commands. You can extend them by adding additional *modules* that serve your purpose.

To download and use the *Done.Land PowerShell Tools*, run this line:

```powershell
Install-Module -Name DoneLandTools -Scope CurrentUser -Force
```

> [!TIP]
> The switch `-Force` omits confirmation dialogs. If you'd rather see them, omit `-Force`. Modules are downloaded from the *Microsoft PowerShell Gallery*. Since this is a *public* place, and *Microsoft* is not taking responsibility for any materials you download from there, you need to confirm your choice.

### Module Installation Fails

Should the above command be unable to download the module, check these items:

* **Internet:** obviously you need to have internet access. Try visiting the [PowerShell Gallery](https://www.powershellgallery.com/) directly. 
* **Permissions:** within company networks, access to the gallery may be restricted.
* **Outdated:** *Windows PowerShell* may use outdated libraries. Try updating them using this command: `Install-Module -Name PowerShellGet -Scope CurrentUser -Force`

## New DoneLand Commands

To see the new **PowerShell** commands the *DoneLandTools* module provides, run this command: `Get-Command -Module DoneLandTools`.

To test-drive the module, here are a few commands you can try:


### FAT32 Formatting Removable Media

`Show-Fat32Converter` shows a dialog window that lets you convert and format *any removable drive* in just a few seconds to the *FAT32* file system.

> [!CAUTION]
> This particular command runs on *Windows* only because internally it uses a binary executable. This command was designed to overcome a specific *Windows* restriction: beginning in *Windows 10*, Microsoft removed the ability to format removable media larger than *32GB* using *FAT32* (which is bad because numerous DIY devices can only read *FAT32*)

```powershell
Show-Fat32Converter
```




> Tags: PowerShell, Module, Install, Tools

:eye:&nbsp;[Visit Page on Website](https://done.land/tools/powershell?054719030921245730) - last edited 2024-03-21

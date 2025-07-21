<img src="/assets/images/butler.jpg" width="80%" height="80%" />
 
# New PowerShell Functions

> Previewing Latest PowerShell Functions


New PowerShell functions are extensively tested before they eventually are merged into the [free PowerShell module](https://done.land/tools/powershell/#install-donelandtools) `donelandtools`.

If you'd like to have a peek, or participate in testing, you'll find the latest function source codes [here](https://github.com/TobiasPSP/doneland_sources/tree/main/Tools/PowerShell/Functions).

## Cleaning Computer Disk Drives: `Get-FolderSize`

You can never have enough disk space on a computer, and with older notebooks, disk drives seem to always be low on space.

That's especially critical when you try and perform major upgrades. For example, if you plan to upgrade from *Windows 10* to *Windows 11*, this requires 10-20GB of free disk space.

> [!TIP]
> Unfortunately, many software vendors start to make *Windows 11* a requirement for their software. For example, `Fusion360` announced there will be no new versions running on *Windows 10*, and beginning 2026, **Windows 11 will be required**. 

It's hard to clean up disk space, though, especially since many Gigabytes of wasted data are hidden away in deeply nested subfolders, and often such folders are marked *hidden* and not visible in *Windows Explorer*.

That's when `Get-FolderSize` comes to the rescue: it examines folder trees (like your personal user profile) and even entire disks, then reports the sizes of all folders and subfolders (including hidden) **individually**. This way you can clearly identify the actual folders that hog massive data.

It also reports back the largest file found in each folder.

Here is a sample call that examines drive `C:\` for any folder larger than *1000MB*, including normally hidden folders:

````powershell
Get-ChildItem -Path c:\ -Recurse -Force -ErrorAction Ignore -File |
  Get-FolderSize -ThresholdSizeMB 1000 |
  Out-GridView
````

The result is displayed in real time in a gridview window. Once all results are in, you can sort the list by clicking column headers. That makes it simple to identify the folders occupying the most space.

Obviously, you can't just delete such folders and hope for the best. Many folders are vital, and deleting them would cause havok. But **identifying these folders** as a first step gives you a clue where it is worthwhile investigating further. When in doubt, I discussed folder paths with one of the readily available **AI Chats** (like *ChatGPT* or *perplexity.ai*), and this way it was simple to identify the purpose of unknown subfolders, and more often than not identify space hogs that could be safely deleted.

### Test Findings

To my honest surprise, the tool found quite a lot of gigabytes of unneeded data that could easily be removed:

* **VSCode:**    
  This editor is great, however it seems to hog massive amounts of temporary data in a variety of subfolders that may stem from long-ago projects, and would be automatically re-downloaded on demand if needed in the future.
* **ArduinoIDE 15.0:**   
  This IDE proved to be a space hog, keeping massive amounts of ZIP files in a subfolder called *staging*. Apparently, these ZIP files are unpacked during installation but then left behind, not needed anymore during normal operation.
* **Installation Location:**
  Most software installs on `C:\` by default, so this drive quickly fills up. Tools like `KiCAD`, `Fusion360`, and *3D slicers* turned out to occupy Gigabytes of data.
  * Uninstall all software that you don't really need.
  * Reinstall all software that you **do need**, and freshly install it to a better location. For example, my notebook has a `D:\` partition with plenty of free space. I ended up uninstalling `KiCAD`, then reinstalling it on my drive `D:`, relieving the memory pressure from the holy `C:\` drive. `Fusion360`, also a **huge memory hog**, unfortunately cannot be configured to use any drive other than `C:\`.

> [!TIP]
> Make sure to also run `cleanmgr.exe` with local Admin privileges, then initiate a system scan. There may be gigabytes of wasted space in log files or older windows installation remnants that can be easily freed with this tool.

### Happy Results

When I started this, my notebook had **2.3-4.7GB** free space on `C:\`. It was a constant struggle to clean up files to keep things going.

After a 30 minute cleanup session, and with the help of `Get-FolderSize`, my drive `C:\` now has **21.8GB** free space, and I was finally able to upgrade to *Windows 11*. The notebook feels and works much better now with a fresh OS and plenty of space.

> [!TIP]
> My notebook originally did not qualify for a *Windows 11 upgrade* despite being from *2018*. I then learned that while there are many items on the prerequisite check list that make sense, most older computers are hit by *CPU requirements* that feel weird: even an **Intel i5** with plenty of power is (officially) not supported to perform a *Windows 11* upgrade. I then used [a PowerShell script](https://github.com/Ad3t0/DirectWindowsUpgrade) to force an upgrade on my old *i5* notebook to *Windows 11*, and it runs smoothly ever since. Just make sure you download the appropriate *Windows 11 ISO Image* that in fact matches your current *Windows 10 edition*, or else your existing license will not be transitioned, and you need a new one. 



> Tags: PowerShell, Disk, CLeanup, Space, Get-FolderSize, Fusion360, KiCAD, Windows 11

[Visit Page on Website](https://done.land/tools/powershell/functions?867238072020254800) - created 2025-07-19 - last edited 2025-07-19

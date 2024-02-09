function Get-SystemFolderPathForDownload
{
  $GuidDownloads = '374DE290-123F-4565-9164-39C4925E467B'
  
  $signature = @'
    [DllImport("shell32.dll", CharSet = CharSet.Unicode)]public extern static int SHGetKnownFolderPath(
    ref Guid folderId, 
    uint flags, 
    IntPtr token,
    out IntPtr pszProfilePath);
'@
  $GetType = Add-Type -MemberDefinition $signature -Name 'GetKnownFolders' -Namespace 'SHGetKnownFolderPath' -Using "System.Text" -PassThru -ErrorAction SilentlyContinue
  $ptr = [intptr]::Zero
  [void]$GetType::SHGetKnownFolderPath([Ref]$GuidDownloads, 0, 0, [ref]$ptr)
  $result = [System.Runtime.InteropServices.Marshal]::PtrToStringUni($ptr)
  [System.Runtime.InteropServices.Marshal]::FreeCoTaskMem($ptr)
  
  if ([string]::IsNullOrWhiteSpace($result))
  {
    $result = Join-Path -Path "$env:temp$env:tmpdir" -ChildPath Downloads
  }
  return $result
}
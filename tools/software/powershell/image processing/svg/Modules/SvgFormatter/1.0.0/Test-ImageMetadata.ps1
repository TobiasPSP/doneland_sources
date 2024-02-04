function Test-ImageMetaData
{
    param
    (
        [Parameter(Mandatory)]
        $Path
    )

    $image = New-Object -ComObject Wia.ImageFile
    $image.LoadFile($Path)
    $image 
}

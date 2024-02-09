function Test-HexValue
{
    param
    (
        [Parameter(Mandatory)]
        [string]
        $Value
    )

    if ($Value.StartsWith('#')) { return $true }
    try
    {
        $null = [Convert]::ToInt64($Value, 16)
        return $true
    }
    catch
    {
        return $false
    }
}
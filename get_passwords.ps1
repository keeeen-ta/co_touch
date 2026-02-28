$onedrive = if ($env:OneDriveCommercial) { $env:OneDriveCommercial } else { $env:OneDrive }
$kdbx = "$onedrive\Apps\KeePassXC\password.kdbx"
$ss = Read-Host "KeePassXC master password" -AsSecureString
$ptr = [System.Runtime.InteropServices.Marshal]::SecureStringToBSTR($ss)
$mp = [System.Runtime.InteropServices.Marshal]::PtrToStringAuto($ptr)
[System.Runtime.InteropServices.Marshal]::ZeroFreeBSTR($ptr)
$pw1 = echo $mp | keepassxc-cli show -sa password $kdbx ActiveDirectory 2>$null
$pw2 = echo $mp | keepassxc-cli show -sa password $kdbx KeePassXC 2>$null
$outfile = "$env:TEMP\kb_build_secrets.tmp"
Set-Content -Path $outfile -Value "$pw1`n$pw2"

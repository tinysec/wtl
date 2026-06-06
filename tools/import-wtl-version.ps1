param(
    [Parameter(Mandatory = $true)]
    [string]$Version,

    [Parameter(Mandatory = $true)]
    [string]$SourceRoot
)

Set-StrictMode -Version Latest
$ErrorActionPreference = "Stop"

$repoRoot = Resolve-Path (Join-Path $PSScriptRoot "..")
$sourceInclude = Resolve-Path (Join-Path $SourceRoot "$Version\Include")
$targetInclude = Join-Path $repoRoot "include\wtl"
$repoRootFull = [System.IO.Path]::GetFullPath($repoRoot)
$repoRootPrefix = $repoRootFull.TrimEnd('\', '/') + [System.IO.Path]::DirectorySeparatorChar
$targetFull = [System.IO.Path]::GetFullPath($targetInclude)

if (-not $targetFull.StartsWith($repoRootPrefix, [System.StringComparison]::OrdinalIgnoreCase)) {
    throw "Refusing to update a target outside the repository: $targetFull"
}

if (-not (Test-Path -LiteralPath $targetInclude)) {
    New-Item -ItemType Directory -Path $targetInclude | Out-Null
}

Get-ChildItem -LiteralPath $targetInclude -Force | Remove-Item -Recurse -Force
Get-ChildItem -LiteralPath $sourceInclude -File | Copy-Item -Destination $targetInclude

$cmakeLists = Join-Path $repoRoot "CMakeLists.txt"
$cmakeText = Get-Content -LiteralPath $cmakeLists -Raw
$cmakeText = $cmakeText -replace 'set\(WTL_VERSION "[^"]+"\)', "set(WTL_VERSION `"$Version`")"
Set-Content -LiteralPath $cmakeLists -Value $cmakeText -Encoding ASCII -NoNewline

$workflow = Join-Path $repoRoot ".github\workflows\ci.yaml"
$workflowText = Get-Content -LiteralPath $workflow -Raw
$workflowText = $workflowText -replace 'WTL_VERSION: [^\r\n]+', "WTL_VERSION: $Version"
Set-Content -LiteralPath $workflow -Value $workflowText -Encoding ASCII -NoNewline

$readme = Join-Path $repoRoot "README.md"
$readmeText = Get-Content -LiteralPath $readme -Raw
$readmeText = $readmeText -replace 'Windows Template Library [0-9][0-9A-Za-z.\-]* as a CMake header-only\s+dependency\.', "Windows Template Library $Version as a CMake header-only`ndependency."
$readmeText = $readmeText -replace 'find_package\(wtl [0-9][0-9A-Za-z.\-]* EXACT CONFIG REQUIRED\)', "find_package(wtl $Version EXACT CONFIG REQUIRED)"
$readmeText = $readmeText -replace 'find_package\(wtl [0-9][0-9A-Za-z.\-]* CONFIG REQUIRED\)', "find_package(wtl $Version CONFIG REQUIRED)"
Set-Content -LiteralPath $readme -Value $readmeText -Encoding ASCII -NoNewline

Write-Host "Imported WTL $Version from $sourceInclude"

param(
    [string]$Configuration = "Release",
    [string]$BuildDir = "build",
    [string]$OutDir = "dist"
)

$asi = Join-Path $BuildDir (Join-Path $Configuration "BattleCreator.asi")
if (-not (Test-Path $asi)) {
    throw "Build BattleCreator.asi first with .\build.ps1."
}

$modOutDir = Join-Path $OutDir "BattleCreator"
New-Item -ItemType Directory -Force -Path $modOutDir | Out-Null

$packageFiles = @(
    $asi,
    "BattleCreator.ini",
    "BattleCreatorCustomPeds.ini",
    "README.md"
)

foreach ($file in $packageFiles) {
    Copy-Item -LiteralPath $file -Destination $modOutDir -Force
}

$zip = "BattleCreator.zip"
if (Test-Path $zip) {
    Remove-Item -LiteralPath $zip -Force
}

Compress-Archive -Path (Join-Path $modOutDir "*") -DestinationPath $zip -Force
Write-Host "Created $zip"


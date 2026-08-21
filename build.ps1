param(
    [string]$ScriptHookRdr2Sdk = $env:SCRIPTHOOKRDR2_SDK,
    [string]$ScriptHookRdr2LibDir = $env:SCRIPTHOOKRDR2_LIB_DIR,
    [string]$Configuration = "Release",
    [string]$BuildDir = "build",
    [string]$CMakePath = $env:CMAKE_EXE
)

$ErrorActionPreference = "Stop"

if (-not $ScriptHookRdr2Sdk) {
    $localSdk = Get-ChildItem -Directory -Path "third_party" -Filter "ScriptHookRDR2_SDK*" -ErrorAction SilentlyContinue |
        Where-Object { Test-Path (Join-Path $_.FullName "inc\natives.h") } |
        Select-Object -First 1

    if ($localSdk) {
        $ScriptHookRdr2Sdk = $localSdk.FullName
    }
}

if (-not $ScriptHookRdr2Sdk) {
    throw "Provide -ScriptHookRdr2Sdk, set SCRIPTHOOKRDR2_SDK, or place the ScriptHookRDR2 SDK under third_party\ScriptHookRDR2_SDK."
}

if (-not $ScriptHookRdr2LibDir) {
    $candidate = Join-Path $ScriptHookRdr2Sdk "lib"
    if (Test-Path (Join-Path $candidate "ScriptHookRDR2.lib")) {
        $ScriptHookRdr2LibDir = $candidate
    }
}

if (-not $ScriptHookRdr2LibDir) {
    throw "Provide -ScriptHookRdr2LibDir, set SCRIPTHOOKRDR2_LIB_DIR, or use an SDK folder containing lib\ScriptHookRDR2.lib."
}

$cmakeExe = $CMakePath
if (-not $cmakeExe) {
    $cmakeCommand = Get-Command cmake -ErrorAction SilentlyContinue
    $cmakeExe = if ($cmakeCommand) { $cmakeCommand.Source } else { $null }
}

if (-not $cmakeExe) {
    $searchRoots = @(
        "$env:ProgramFiles\CMake",
        "${env:ProgramFiles(x86)}\CMake",
        "$env:ProgramFiles\Microsoft Visual Studio",
        "${env:ProgramFiles(x86)}\Microsoft Visual Studio"
    ) | Where-Object { $_ -and (Test-Path $_) }

    foreach ($root in $searchRoots) {
        $found = Get-ChildItem $root -Recurse -Filter cmake.exe -ErrorAction SilentlyContinue |
            Select-Object -First 1 -ExpandProperty FullName
        if ($found) {
            $cmakeExe = $found
            break
        }
    }
}

if (-not $cmakeExe) {
    throw "CMake is not available in this shell. Install CMake or run this from an environment where cmake is on PATH."
}

if (-not (Test-Path -LiteralPath $cmakeExe)) {
    throw "CMake was found or provided at '$cmakeExe', but that file does not exist."
}

& $cmakeExe -S . -B $BuildDir -DSCRIPTHOOKRDR2_SDK="$ScriptHookRdr2Sdk" -DSCRIPTHOOKRDR2_LIB_DIR="$ScriptHookRdr2LibDir"
if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }

& $cmakeExe --build $BuildDir --config $Configuration
exit $LASTEXITCODE

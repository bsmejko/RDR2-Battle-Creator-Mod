# Battle Creator for RDR2

Battle Creator is a ScriptHookRDR2 mod for Red Dead Redemption 2 that lets the player set up NPC battles from an in-game menu. It supports team battles, battle royale rounds, point-based deathmatch modes, custom NPC groups, boss characters, special characters, spectator camera, blips, leaderboards, battle modifiers, presets, and INI-driven balance tuning.

## Requirements

- Red Dead Redemption 2 for PC.
- ScriptHookRDR2.
- An ASI loader compatible with RDR2.
- For building from source: CMake and a Windows C++ build environment.

## Build From Source

This repository does not include ScriptHookRDR2 SDK files or game files.

Build with:

```powershell
.\build.ps1 -ScriptHookRdr2Sdk "C:\Path\To\ScriptHookRDR2_SDK" -ScriptHookRdr2LibDir "C:\Path\To\ScriptHookRDR2_SDK\lib"
```

If CMake is not on `PATH`, pass it explicitly:

```powershell
.\build.ps1 -CMakePath "C:\Path\To\cmake.exe" -ScriptHookRdr2Sdk "C:\Path\To\ScriptHookRDR2_SDK" -ScriptHookRdr2LibDir "C:\Path\To\ScriptHookRDR2_SDK\lib"
```

Or set these environment variables before building:

```powershell
$env:SCRIPTHOOKRDR2_SDK = "C:\Path\To\ScriptHookRDR2_SDK"
$env:SCRIPTHOOKRDR2_LIB_DIR = "C:\Path\To\ScriptHookRDR2_SDK\lib"
.\build.ps1
```

Create the release zip with:

```powershell
.\package.ps1
```

The package contains `BattleCreator.asi`, `BattleCreator.ini`, `BattleCreatorCustomPeds.ini`, and `README.md`.

## Install

Put these files in the main RDR2 game folder, next to `RDR2.exe`:

- `BattleCreator.asi`
- `BattleCreator.ini`
- `BattleCreatorCustomPeds.ini`

`BattleCreatorPresets.ini` is created automatically in the game folder when a battle preset is saved.

## Quick Start

1. Launch story mode.
2. Press `F9` to open the Battle Creator menu.
3. Choose a mode: Team Survival, Battle Royale, Team Deathmatch, or Free For All.
4. Choose the battle type: All Weapons, Melee Only, or No Weapons.
5. Add sets of fighters. A set is something like `10x Medium O'Driscolls` or `1x Boss John Marston`.
6. Press Start Battle.
7. Press `K` during a battle to spectate living NPCs. Press `K` again to exit spectator camera.
8. Clear the battle to show the leaderboard.

## Controls

- `F9`: open or close the Battle Creator menu. Also clears the post-battle leaderboard.
- `Up/Down`: move through menu rows.
- `Left/Right`: change the selected menu option.
- `Shift + Left/Right`: larger steps for supported numeric rows.
- `1-4`: jump straight to Team 1, Team 2, Team 3, or Team 4 in team modes.
- `N`: randomize the current mode setup.
- `R`: reload `BattleCreator.ini` and `BattleCreatorCustomPeds.ini` while the menu is open.
- `K`: enter or exit spectator camera during an active battle.
- `Left/Right` while spectating: switch spectator target.
- `K` on the leaderboard: toggle leaderboard view.
- `Enter` or `Space`: activate the selected row, start the battle, or clear the battle.
- `Delete`: clear the current battle.

The settings menu uses smoother held left/right input for numeric values. Settings apply immediately for the current session, then persist to `BattleCreator.ini` only when `Save settings` is pressed.

## Battle Modes

### Team Survival

One-life team battle mode.

- Up to four teams can be configured.
- Each team can contain multiple sets with different ped groups and difficulties.
- Empty teams are disabled.
- Each team relation to the player can be Friendly, Neutral, or Hostile.
- Friendly teams count the player as part of the team while the player is alive.
- If the player dies in a survival battle, the player is removed from the round and becomes a spectator.
- The round ends when only one active side remains.

Example team:

```text
Team 1: 10x Medium O'Driscolls + 1x Boss Dutch Van Der Linde
```

### Battle Royale

One-life free-for-all mode.

- There are no team slots.
- Add as many bulk sets as desired, such as `20x Army`, `5x Van der Linde Gang`, or `1x Boss John Marston`.
- Fighters spawn scattered around the player area instead of in team lines.
- Team size can be Solo, Duo, Trios, or Squad.
- In Play mode, all enemy groups are hostile to the player.
- In Spectate mode, the player is neutral and hidden while spectating.
- The round ends when only one fighter or one squad remains.

### Team Deathmatch

Point-based team mode.

- Uses the same team setup as Team Survival.
- Fighters respawn after death.
- The player respawns back into the match if participating.
- The first team to reach the kill limit wins.
- Set the score limit to `0` for an endless match that runs until cleared manually.
- Optional setting: Team Deathmatch NPCs can respawn at their original battle spawn point.
- The leaderboard tracks kills, deaths, and KD ratio.
- The `K` leaderboard toggle switches between individual stats and team stats.

### Free For All

Point-based free-for-all mode.

- Uses the same set builder as Battle Royale.
- Fighters respawn after death.
- Solo, Duo, Trios, and Squad team sizes are supported.
- The first fighter or squad to reach the kill limit wins.
- Set the score limit to `0` for an endless match that runs until cleared manually.
- The compact HUD shows the player's kills and the current leading score out of the goal.
- The `K` leaderboard toggle switches between individual stats and KD/squad views depending on team size.

## Battle Types

- `All Weapons`: fighters use their configured firearms and melee backups. Bosses and Specials may have custom loadouts.
- `Melee Only`: firearms are removed and fighters receive melee weapons.
- `No Weapons`: all weapons are removed for fist fights.

Default spawn spacing:

| Type | Default value |
| --- | ---: |
| All Weapons | 26 |
| Melee Only | 12 |
| No Weapons | 8 |

Team modes use this value as distance between team formations. Free-for-all modes use it as the scatter radius. In team modes, Team 1 stays close in front of the player so the player starts behind the likely friendly side instead of in the middle of the fight.

Spawn placement asks the game for nearby safe pedestrian/navmesh coordinates, avoids already spawned battle peds, retries around blocked points, and can expand toward nearby road/path nodes in towns. This helps large town battles fit more fighters, but very high radii can still push fighters into unloaded or awkward pathing areas.

If `Manual team spawns` is enabled in Settings, team modes show `Set Spawn` and `Clear Spawn` under the selected team. `Set Spawn` saves Arthur's current position for that team and draws a ground ring there: hostile red, neutral blue, friendly green. Team Survival and Team Deathmatch then spawn that team at the saved ring until the point is cleared, replaced, or the current battle is cleared.

## Player And Spectator Behaviour

- Friendly teams cannot be turned hostile by accidental player damage.
- Player damage to friendly battle peds is blocked/restored.
- Hostile teams attack the player.
- Neutral teams ignore the player but still fight hostile NPC sides. If `NeutralsFriendlyUntilAttacked` is enabled, neutral teams become hostile to the player after the player damages one of their members.
- Wanted status can be suppressed during battles.
- Player death is intercepted where possible to avoid the long normal respawn flow.
- In survival modes, a dead participating player becomes a spectator.
- In deathmatch modes, a dead participating player respawns into the match.
- Spectator camera hides, freezes, and makes the player invincible while active.
- If Force Spectator is enabled, the player automatically spectates after being eliminated.
- Spectator camera targets are limited by `SpectatorMaxTargetDistance` by default, which helps avoid far terrain/collision streaming issues in huge-radius battles. Set it to `0` in the INI for unlimited target cycling.
- Player health, stamina, Dead Eye, and cores are refilled when battles are cleared or after battle cleanup.

## Blips

- Hostile fighters: red blips.
- Neutral fighters: blue blips.
- Friendly fighters: green blips.
- Bosses: bounty-style blips where available, with a slightly larger scale.

## Leaderboards

Leaderboards stay visible until `F9` is pressed.

- Survival modes show kills and finishing position.
- Team Survival can toggle to team elimination order with total team kills.
- Battle Royale can show individual placement; duo/trio/squad members share the same placement.
- Team Deathmatch shows kills, deaths, and KD ratio, with a team-stat toggle.
- Free For All shows kills, deaths, and KD ratio, with KD/squad views depending on team size.
- The player is included if they participated, even if they later died and became a spectator.
- Pure spectator players are not included.
- The NPC who killed the player is marked with `(killed you)`.
- Up to 64 entries are displayed.

## Built-In Ped Sets

Normal ped sets can be spawned at Easy, Medium, Hard, or Extreme difficulty. Bosses and Specials are selected separately.

| Ped set | Model pool | Firearms | Melee |
| --- | --- | --- | --- |
| Bounty Hunters | `S_M_M_BOUNTYHUNTER_01`, `G_M_M_UNIBOUNTYHUNTER_01`, `G_M_M_UNICRIMINALS_01`, `S_M_M_DISPATCHLEADERPOLICE_01`, `S_M_M_AMBIENTLAWRURAL_01` | Carbine repeater, bolt-action rifle, cattleman revolver | Knife, hatchet, machete |
| O'Driscolls | `G_M_M_UNIDUSTER_01`, `G_M_M_UNICRIMINALS_01`, `G_M_M_UNIMOUNTAINMEN_01`, `G_M_M_UNIRANCHERS_01`, `A_M_M_GRIFANCYTRAVELLERS_01` | Carbine repeater, double-barrel shotgun, cattleman revolver | Knife, hatchet, machete |
| Lawmen | `S_M_M_AMBIENTLAWRURAL_01`, `S_M_M_DISPATCHLEADERPOLICE_01`, `S_M_M_VALDEPUTY_01`, `S_M_M_STRDEPUTY_01`, `S_M_M_RHDDEPUTY_01` | Carbine repeater, cattleman revolver, bolt-action rifle | Knife, machete, hatchet |
| Lemoyne Raiders | `G_M_M_UNIRAIDERS_01`, `G_M_M_UNICRIMINALS_01`, `G_M_M_UNIGRAYS_01`, `G_M_M_UNIBRAITHWAITES_01`, `A_M_M_BLUROUGHWORKERS_01` | Carbine repeater, double-barrel shotgun, cattleman revolver | Machete, knife, hatchet |
| Del Lobos | `G_M_M_UNIBANDITOS_01`, `G_M_M_UNICRIMINALS_01`, `G_M_M_UNIMOUNTAINMEN_01`, `A_M_M_ARMCHOLERACORPSE_01`, `A_M_M_TUMTOWNFOLK_01` | Carbine repeater, cattleman revolver, sawed-off shotgun | Machete, knife, hatchet |
| Murfree Brood | `G_M_M_UNIINBRED_01`, `G_M_M_UNIMOUNTAINMEN_01`, `G_M_M_UNICRIMINALS_01`, `A_M_M_BIVROUGHWORKERS_01`, `A_M_M_BIVWORKINGMEN_01` | Double-barrel shotgun, carbine repeater, cattleman revolver | Machete, knife, hatchet |
| Skinner Brothers | `G_M_M_UNIMOUNTAINMEN_01`, `G_M_M_UNICRIMINALS_01`, `G_M_M_UNIRANCHERS_01`, `A_M_M_TUMTOWNFOLK_01`, `A_M_M_ASBTOWNFOLK_01` | Bolt-action rifle, carbine repeater, double-barrel shotgun | Hatchet, machete, knife |
| Night Folk | `G_M_M_UNICRIMINALS_01`, `G_M_M_UNIINBRED_01`, `A_M_M_BIVROUGHWORKERS_01`, `A_M_M_BIVWORKINGMEN_01`, `A_M_M_LAGTOWNFOLK_01` | Double-barrel shotgun, carbine repeater, cattleman revolver | Machete, knife, hatchet |
| Pinkertons | `S_M_M_PINLAW_01`, `S_M_M_AMBIENTLAWRURAL_01`, `S_M_M_DISPATCHLEADERPOLICE_01`, `G_M_M_UNICORNWALLGOONS_01`, `S_M_M_VALDEPUTY_01` | Bolt-action rifle, carbine repeater, cattleman revolver | Knife, machete, hatchet |
| Army | `S_M_M_ARMY_01`, `S_M_Y_ARMY_01`, `G_M_M_UNICORNWALLGOONS_01`, `S_M_M_AMBIENTLAWRURAL_01`, `G_M_M_UNICRIMINALS_01` | Bolt-action rifle, carbine repeater, cattleman revolver | Knife, hatchet, machete |
| Van der Linde Gang | Hosea Matthews, Lenny Summers, Sean MacGuire, Kieran Duffy, Sadie Adler | Carbine repeater, cattleman revolver, double-barrel shotgun | Knife, machete, hatchet |
| Micah's Gang | Cleet, Joe, Micah Gunman 1, Micah Gunman 2, Micah Gunman 3 | Carbine repeater, cattleman revolver, double-barrel shotgun | Knife, machete, hatchet |

The named gang sets avoid duplicate named characters within the same fight where possible. Bosses and Specials are not included in the Van der Linde set and should be added separately.

## Difficulties

The global movement multiplier from `[Battle]` is applied on top of each `MoveRate`. The default global multiplier is `1.08`.

| Difficulty | Health | Accuracy | ShootRate | MoveRate | Combat ability | Combat movement | Combat range | Hardened | Heals | Approach / Retask / Burst |
| --- | ---: | ---: | ---: | ---: | ---: | ---: | ---: | --- | --- | --- |
| Easy | 60 | 10-30 | 250 | 0.96 | 0 | 1 | 0 | No | No | 2700 / 3600 / 1900 ms |
| Medium | 100 | 30-50 | 450 | 1.04 | 1 | 2 | 0 | No | No | 2100 / 2800 / 1300 ms |
| Hard | 180 | 50-70 | 650 | 1.12 | 2 | 3 | 1 | No | No | 1600 / 2200 / 900 ms |
| Extreme | 300 | 85-100 | 900 | 1.14 | 2 | 3 | 1 | Yes | No | 1200 / 1800 / 700 ms |
| Special base | 300 | 70-90 | 850 | 1.08 | 2 | 3 | 1 | Yes | No | 1500 / 2000 / 950 ms |
| Bosses base | 500 | 100 | 1000 | 1.05 | 2 | 3 | 1 | Yes | Yes | 1000 / 1500 / 550 ms |

Combat ability values are native values where `0` is poor, `1` is average, and `2` is professional. Combat movement values are native values where `0` is stationary, `1` is defensive, `2` advances, and `3` is offensive.

## Bosses

Bosses override the generic Bosses difficulty. All bosses are hardened, use 100 accuracy, resist ragdoll-style knockdowns where possible, heal slowly after avoiding damage, and have execution/critical protection above the boss threshold.

Boss healing defaults:

- Gunfight healing starts after 12000 ms without damage.
- Melee healing starts after 14000 ms without damage.
- Gunfight healing ticks every 5500 ms.
- Melee healing ticks every 7000 ms.
- Heal amount is 1 health per tick.
- Healing is capped at the boss's configured max health.

Boss execution/critical protection:

- Bosses are protected above 60 health.
- Cinematic executions above 60 health deal 35 damage and the boss recovers.
- At 60 health or below, natural executions and critical finishers are allowed.

| Boss | Models tried | Outfit | Health | Accuracy | ShootRate | MoveRate | Approach / Retask / Burst | Shot / Wounded shot | Evasion cooldown | Slide chance close/far | Dead Eye block |
| --- | --- | ---: | ---: | ---: | ---: | ---: | --- | --- | ---: | --- | ---: |
| John Marston | `CS_JOHNMARSTON`, `CS_JOHNMARSTON_REV`, fallback townfolk | 18 | 500 | 100 | 3950 | 1.30 | 650 / 650 / 160 ms | 1850 / 1000 ms | 5200 ms | 100 / 100 | 100 |
| Dutch Van Der Linde | `CS_DUTCH`, `CS_DUTCHVANDERLINDE`, `CS_DUTCH_02`, `U_M_M_STORY_DUTCH` | 5 | 500 | 100 | 1120 | 1.00 | 1450 / 1650 / 850 ms | 1250 / 950 ms | 9200 ms | 8 / 3 | 28 |
| Micah Bell | `CS_MICAH_BELL`, `CS_MICAHBELL`, `CS_MICAH`, `U_M_M_STORY_MICAH` | 21 | 500 | 100 | 2600 | 1.08 | 650 / 850 / 260 ms | 2850 / 1100 ms | 5600 ms | 46 / 28 | 100 |
| Colm O'Driscoll | `CS_COLMODRISCOLL`, `CS_COLM_ODRISCOLL`, `U_M_M_STORY_COLM`, fallback duster | 3 | 500 | 100 | 1380 | 1.00 | 1250 / 1350 / 620 ms | 1350 / 950 ms | 6900 ms | 22 / 12 | 45 |
| Arthur Morgan | `PLAYER_ZERO` | 0 | 600 | 100 | 3950 | 1.30 | 650 / 650 / 160 ms | 1850 / 1000 ms | 5200 ms | 100 / 100 | 100 |

Boss combat profiles:

- John Marston: aggressive mixed-range gunslinger. Uses shotgun at close range, carbine repeater at mid range, bolt-action rifle at long range, frequent large dodges, fast fire rate, and strong player-facing dodge pressure.
- Arthur Morgan: same core behaviour as John, with 600 health.
- Dutch Van Der Linde: cover and long-range focused. Uses Schofield revolver close and bolt-action rifle at medium/long range. His landed shots apply bonus damage to make him feel more like a sharpshooter.
- Micah Bell: aggressive close/mid-range killer. Uses Micah's double-action revolver with an offhand double-action revolver setup, longer rapid-fire pressure, and high Dead Eye block chance on big dodges.
- Colm O'Driscoll: simplest boss. Uses his default/current weapon where possible, prioritizes cover, dodges less than John/Micah, and remains accurate/aggressive.

John, Micah, and Arthur have 100 percent temporary player Dead Eye block chance on large boss dodges. Dutch and Colm have lower chances.

## Specials

Specials are not bosses, but they use custom Extreme-level profiles and protection above the Extreme/Special threshold.

Special execution/critical protection:

- Specials are protected above 120 health.
- Cinematic executions above 120 health deal 35 damage and the fighter recovers.
- At 120 health or below, natural executions and critical finishers are allowed.

| Special | Models tried | Outfit | Health | Accuracy | ShootRate | MoveRate | Movement / Range | Melee specialist | Approach / Retask / Burst |
| --- | --- | ---: | ---: | ---: | ---: | ---: | --- | --- | --- |
| Javier Escuella | `CS_JAVIERESCUELLA`, `CS_JAVIER_ESCUELLA`, `U_M_M_STORY_JAVIERESCUELLA` | 1 | 245 | 88-100 | 1380 | 1.48 | 3 / 2 | No | 700 / 900 / 390 ms |
| Bill Williamson | `CS_BILLWILLIAMSON`, `CS_BILL_WILLIAMSON`, `U_M_M_STORY_BILLWILLIAMSON` | 12 | 430 | 55-72 | 760 | 1.00 | 1 / 1 | Yes | 1800 / 2300 / 1200 ms |
| Tommy | `CS_MUD2BIGGUY`, `U_M_M_STORY_MUD2BIGGUY` | 1 | 450 | 45-60 | 760 | 1.18 | 3 / 0 | Yes | 520 / 850 / 900 ms |
| Charles Smith | `CS_CHARLESSMITH`, `CS_CHARLES_SMITH`, `U_M_M_STORY_CHARLESSMITH` | 1 | 460 | 94-100 | 1300 | 1.16 | 3 / 2 | Yes | 850 / 1050 / 520 ms |

Special combat profiles:

- Javier Escuella: very fast, accurate, mobile, and dodge-heavy.
- Bill Williamson: tanky brawler with lower accuracy, strong fists, and a small landed-hit damage bonus.
- Tommy: close-range charger. Uses hatchet, shotgun, and repeater in All Weapons, but strongly prefers closing distance and forcing melee/grapple pressure.
- Charles Smith: stealth/ambush specialist. Uses bow most of the time, with throwing knives and tomahawks for selected opportunities.

## Custom Ped Sets

Custom normal ped groups live in `BattleCreatorCustomPeds.ini`, not the main INI.

Rules:

- Up to 64 custom sets.
- Up to 6 models per set.
- Up to 3 firearms per set.
- Up to 3 melee weapons per set.
- Separate entries with commas and no quotes.
- If firearms or melee weapons are omitted, safe defaults are used.
- Custom sets are normal ped sets. Bosses and Specials still require code support.
- Press `R` in the menu or restart the game/script after editing.

Example:

```ini
[CustomPedSets]
Count=1

[CustomPedSet.1]
Name=Example Townsfolk
Models=A_M_M_VALTOWNFOLK_01,A_M_M_RHDROUGHTRAVELLERS_01
Firearms=WEAPON_REVOLVER_CATTLEMAN,WEAPON_REPEATER_CARBINE,WEAPON_RIFLE_BOLTACTION
MeleeWeapons=WEAPON_MELEE_KNIFE,WEAPON_MELEE_HATCHET,WEAPON_MELEE_MACHETE
```

For upgrade safety, the mod can still read old `[CustomPedSets]` entries from `BattleCreator.ini` if the new custom-ped file is empty.

## Main INI Reference

`BattleCreator.ini` controls the main experience.

- `[Keys]`: menu key. Default `F9`.
- `[Battle]`: spawn distances/radius, cleanup distance, global movement multiplier, max normal team count.
- `[BattleModifiers]`: Force spectator, manual team spawns, neutral retaliation, spectator target range, No Dead Eye, Never wanted, and start countdown.
- `[Deathmatch]`: default/min/max kill limits, endless score limit support, NPC respawn delay, and optional original-point Team Deathmatch respawns.
- `[DeathmatchPerformance]`: cleanup and pacing settings for long-running respawn modes.
- `[Performance]`: corpse cleanup, dropped-weapon cleanup, and distant offscreen battle simulation.
- `[Protection]`: boss/extreme execution thresholds and blocked execution damage.
- `[BossCombat]`: low-health defensive threshold and boss dodge Dead Eye suppression duration.
- `[BossHealing]`: boss healing timing and amount.
- `[Healing]`: optional regular healing timing for non-boss tiers if enabled.
- `[CombatRecovery]`: idle watchdog retasking for NPCs that get stuck.
- `[Difficulty.*]`: base difficulty stats.
- `[Boss.*]`: named boss stat overrides.
- `[Special.*]`: named special stat overrides.

The in-game Settings page exposes the main battle modifiers and common values. Deeper combat, balance, and performance values are left in the INI so published installs can be tuned without recompiling.

Settings changed in-game are not written to disk automatically. Use `Save settings` on the Settings & presets page to update `BattleCreator.ini`.

## Presets

The Settings & presets page supports eight preset slots.

Presets save:

- Battle mode.
- Battle type.
- Kill limit.
- Team rosters.
- Battle Royale / Free For All sets.
- Player Play/Spectate option.
- Solo/Duo/Trios/Squad size.

Presets are stored in `BattleCreatorPresets.ini`, which is created automatically when a preset is saved. Slots become active only after the mod writes `Saved=1` to `Preset1` through `Preset8`.

## Performance And Cleanup

Large RDR2 battles can stress the game engine, especially in cities or with long-running deathmatch modes.

The mod includes:

- Spawn batching during preparation.
- Safer relationship setup pacing.
- Corpse cleanup for normal battles.
- Faster deathmatch corpse cleanup after the configured visible delay.
- Tracked dropped weapon cleanup.
- Large-deathmatch maintenance throttling.
- Snapshot-based target searches in Free For All modes.
- Respawn pacing to avoid spawning too many NPCs in one frame.
- Distant battle simulation, which resolves only offscreen/out-of-range combat pockets. Fighters near the player or spectator camera cannot be selected as simulated killers or victims, and Battle Royale final duels are left to play out naturally.

Default cleanup values:

| Setting | Default |
| --- | ---: |
| Deathmatch corpse visible time | 4000 ms |
| Maximum respawns per frame | 1 |
| Minimum respawn gap | 50 ms |
| Normal corpse lifetime | 30000 ms |
| Elite corpse lifetime | 45000 ms |
| Preferred maximum corpses | 40 |
| Hard maximum corpses | 65 |
| Distant simulation distance | 180 m, adjustable in `BattleCreator.ini` |
| Distant simulation first delay | 2500 ms |
| Distant simulation base tick | 2600 ms, faster in large fights and slower late game |

For maximum stability, avoid extremely high NPC counts in dense towns such as Saint Denis.

## Build From Source

Build Release with:

```powershell
.\build.ps1 -Configuration Release
```

Package Battle Creator with:

```powershell
.\package.ps1 -Configuration Release
```

The Battle Creator ASI output is:

```text
build\Release\BattleCreator.asi
```

The package script creates `BattleCreator.zip` containing:

- `BattleCreator.asi`
- `BattleCreator.ini`
- `BattleCreatorCustomPeds.ini`
- `README.md`

## Notes And Limits

- RDR2 native names can vary between ScriptHook/native databases.
- Execution protection is partly script-side. Some cinematic kill states are detected, damaged, and recovered rather than fully disabled at the native level.
- John and Dutch can also benefit from external `pedhealth.meta` / `metapeds.ymt` edits that use player-style health configs.
- Custom ped sets are for normal selectable ped groups. Named bosses and specials are hardcoded because they need custom stats, loadouts, outfits, and behaviour.
- The mod is designed for single-player story mode.

## Screenshots

<img width="1916" height="1071" alt="Screenshot 2026-07-22 004834" src="https://github.com/user-attachments/assets/92a451c8-f220-4f0c-a3b5-7a7a65320231" />
<img width="1916" height="1071" alt="Screenshot 2026-07-22 004822" src="https://github.com/user-attachments/assets/908f42ee-d332-4601-8820-8fec5b4eab53" />
<img width="2559" height="1287" alt="Screenshot 2026-07-22 000851" src="https://github.com/user-attachments/assets/bee2ae73-6061-4110-8237-5cafc4f709d4" />
<img width="2324" height="1185" alt="Screenshot 2026-07-22 000712" src="https://github.com/user-attachments/assets/32c78056-8431-4999-9dc7-c7d776b73be4" />
<img width="1912" height="1077" alt="Screenshot 2026-07-22 004852" src="https://github.com/user-attachments/assets/1c168c6e-957a-41f9-a648-85439a3d0d81" />


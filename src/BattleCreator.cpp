#include <windows.h>

#include <algorithm>
#include <array>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstddef>
#include <cstdlib>
#include <string>
#include <vector>

#include "natives.h"
#include "types.h"
#include "enums.h"
#include "main.h"

namespace
{
constexpr float kPi = 3.14159265358979323846f;
constexpr int kTeamCount = 4;
constexpr int kRosterSlotCount = 4;
constexpr int kTeamMenuRows = 19;
constexpr int kBattleRoyaleMenuRows = 17;
constexpr int kSettingsMenuRows = 19;
constexpr int kMaxRows = 20;
constexpr int kPresetSlotCount = 8;
constexpr int kNamedGangPedSetIndex = 10;
constexpr int kMicahsGangPedSetIndex = 11;
constexpr int kBossJohn = 0;
constexpr int kBossDutch = 1;
constexpr int kBossMicah = 2;
constexpr int kBossColm = 3;
constexpr int kBossArthur = 4;
constexpr int kSpecialJavier = 0;
constexpr int kSpecialBill = 1;
constexpr int kSpecialTommy = 2;
constexpr int kSpecialCharles = 3;
constexpr Any kRdr2MarkerCylinder = 0x94FDAE17u;
constexpr int kBossExecutionHealthThreshold = 60;
constexpr int kExtremeExecutionHealthThreshold = 120;
constexpr int kBossDefensiveHealthThreshold = 100;
constexpr int kBossBlockedExecutionDamage = 35;
constexpr int kLeaderboardMaxEntries = 64;
constexpr DWORD kLeaderboardToggleKey = 'K';
constexpr const char* kLeaderboardToggleKeyName = "K";
constexpr Hash kInputSpecialAbility = 0x580C4473;
constexpr Hash kInputSpecialAbilitySecondary = 0x811F4A1A;
constexpr float kMaxBattleSpawnDistance = 200.0f;
constexpr float kDefaultSpectatorMaxTargetDistance = 120.0f;
constexpr int kSpawnCreateAttempts = 42;
constexpr int kSpawnSafetySearchAttempts = 144;
constexpr int kSpawnInwardFallbackAttempt = 16;
constexpr float kSpawnInwardFallbackDistance = 78.0f;
constexpr float kSpawnSafetyMaxHeightDelta = 6.0f;
constexpr float kSpawnSafetyWaterMargin = 0.35f;
constexpr float kSpawnStrictMinSpacing = 2.1f;
constexpr float kSpawnRelaxedMinSpacing = 0.95f;
constexpr float kSpawnEmergencyMinSpacing = 0.35f;
constexpr float kSpawnRoofRoadRejectRadius = 11.0f;
constexpr float kSpawnRoofRoadRejectHeight = 2.0f;
constexpr int kWeaponAttachDefault = 0;
constexpr int kWeaponAttachSecondary = 1;
constexpr int kWeaponAttachPistolRight = 2;
constexpr int kWeaponAttachPistolLeft = 3;
constexpr DWORD kExecutionRecoveryMinMs = 0;
constexpr DWORD kExecutionRecoveryMaxMs = 900;
constexpr DWORD kBossDodgeDeadEyeSuppressMs = 750;
constexpr DWORD kBossDynamiteCooldownMs = 26000;
constexpr DWORD kBossAggressionFallbackMs = 1300;
constexpr DWORD kWeaponPendingTimeoutMs = 1800;
constexpr DWORD kWeaponSettleMs = 1150;
constexpr DWORD kWeaponStableRangeMs = 1200;
constexpr DWORD kWeaponSwitchCooldownMs = 4000;
constexpr int kWeaponMaxRetries = 2;
constexpr DWORD kProjectileEquipSettleMs = 850;
constexpr DWORD kProjectileStartGraceMs = 650;
constexpr DWORD kProjectileRetryDelayMs = 1600;
constexpr DWORD kProjectileHardTimeoutMs = 5000;
constexpr DWORD kProjectileFailureCooldownMs = 3500;
constexpr DWORD kBossEvasionCheckMs = 650;
constexpr DWORD kBossEvasionTimeoutMs = 1450;
constexpr DWORD kBossDodgeDeadEyeMinMs = 250;
constexpr DWORD kBossDodgeDeadEyeMaxMs = 1500;
constexpr DWORD kBossDodgeDeadEyeGlobalGraceMs = 700;
constexpr DWORD kMobileBossDashMs = 900;
constexpr DWORD kSlideBossDodgeMs = 520;
constexpr DWORD kNativeDiveStartGraceMs = 180;
constexpr DWORD kPlayerDodgeEligibilityCheckMs = 100;
constexpr DWORD kJohnPlayerDodgeCooldownMs = 2800;
constexpr DWORD kArthurPlayerDodgeCooldownMs = 3000;
constexpr DWORD kPlayerDamageDodgeMinimumGapMs = 1900;
constexpr DWORD kPlayerAimPressureMinMs = 120;
constexpr DWORD kPlayerDashConfirmMs = 110;
constexpr DWORD kPlayerDashFallbackMs = 190;
constexpr DWORD kPlayerDashDurationMs = 660;
constexpr DWORD kRelationshipValidationMs = 5000;
constexpr DWORD kBlipRefreshMs = 750;
constexpr DWORD kDynamiteScanBaseMs = 1300;
constexpr int kSpawnYieldBatchSize = 6;
constexpr DWORD kNormalMaintenanceMs = 50;
constexpr DWORD kEliteMaintenanceMs = 33;
constexpr DWORD kNormalCombatUpdateMs = 125;
constexpr DWORD kEliteCombatUpdateMs = 75;
constexpr DWORD kBlipValidationMs = 900;
constexpr DWORD kDynamicTuningRepairMs = 12000;
constexpr int kPreparationSpawnBatchSize = 5;
constexpr int kPreparationGroupCreatesPerFrame = 3;
constexpr int kPreparationRelationshipSetterBudget = 180;
constexpr int kPreparationFightersPerFrame = 6;
constexpr DWORD kNormalCorpseMinimumLifetimeMs = 30000;
constexpr DWORD kEliteCorpseMinimumLifetimeMs = 45000;
constexpr DWORD kMaximumCorpseLifetimeMs = 90000;
constexpr DWORD kCorpseCleanupCheckMs = 2000;
constexpr float kCorpseCleanupMinPlayerDistance = 35.0f;
constexpr int kPreferredMaximumBattleCorpses = 40;
constexpr int kHardMaximumBattleCorpses = 65;
constexpr int kCorpseCleanupFightersPerTick = 8;
constexpr int kCorpseCleanupDetachedPerTick = 6;
constexpr int kCorpseCleanupDeletesPerTick = 2;
constexpr float kDefaultDistantBattleSimulationDistance = 180.0f;
constexpr DWORD kDefaultDistantBattleSimulationDelayMs = 2500;
constexpr DWORD kDefaultDistantBattleSimulationTickMs = 2600;
constexpr Hash kTaskHashThrowProjectile = 0;
constexpr int kBossDynamiteMinClusterTargets = 4;
constexpr float kBossDynamiteClusterRadius = 7.5f;
constexpr float kBossDynamiteMinThrowDistance = 13.0f;
constexpr float kBossDynamiteMaxThrowDistance = 58.0f;
constexpr float kBossDynamitePlayerSafetyRadius = 11.0f;
constexpr int kPedConfigFlagNoCriticalHits = 2;
constexpr int kPedConfigFlagProtectedNoCriticalHits = 263;
constexpr int kPedConfigFlagDisableHeadGore = 305;
constexpr int kPedConfigFlagDisableLimbGore = 306;
constexpr float kProtectedHeadshotTestMultiplier = 0.0f;
constexpr int kPedResetFlagSuppressLethalMeleeActions = 31;
constexpr int kPedResetFlagPreventAllMeleeTakedowns = 36;
constexpr int kPedResetFlagPreventFailedMeleeTakedowns = 37;
constexpr int kActionFailedTakedown = 14;
constexpr int kActionTakedown = 15;
constexpr int kActionExecution = 16;
constexpr int kActionStealthKill = 17;
constexpr bool kUsePersistentExecutionActionDisable = false;
constexpr DWORD kPlayerBattleReviveDelayMs = 4500;
constexpr DWORD kPlayerSpectatorReviveDelayMs = 3450;
constexpr DWORD kPlayerScreenRepairAfterReviveMs = 6000;
constexpr DWORD kNpcDeathmatchRespawnDelayMs = 4800;
constexpr DWORD kDeathmatchCorpseVisibleMs = 4000;
constexpr int kDeathmatchMaxRespawnsPerFrame = 1;
constexpr DWORD kDeathmatchRespawnGapMs = 50;
constexpr DWORD kDeathmatchSnapshotRefreshMs = 200;
constexpr int kDeathmatchMaxFullRetargetsPerFrame = 10;
constexpr int kLargeDeathmatchThreshold = 50;
constexpr DWORD kLargeDeathmatchCombatUpdateMs = 160;
constexpr DWORD kLargeDeathmatchBlipValidationMs = 1800;
constexpr DWORD kLargeDeathmatchDynamicRepairMs = 25000;
constexpr DWORD kSoloFfaIdleCheckMs = 2800;
constexpr DWORD kSoloFfaIdleThresholdMs = 5000;
constexpr DWORD kCompactHudRefreshMs = 160;
constexpr DWORD kMenuInputRepeatInitialMs = 230;
constexpr DWORD kMenuInputRepeatMs = 60;
constexpr int kDefaultDeathmatchKillLimit = 25;
constexpr int kMinDeathmatchKillLimit = 0;
constexpr int kMaxDeathmatchKillLimit = 500;
constexpr const char* kBattleCreatorIni = ".\\BattleCreator.ini";
constexpr const char* kBattleCreatorCustomPedsIni = ".\\BattleCreatorCustomPeds.ini";
constexpr const char* kBattleCreatorPresetsIni = ".\\BattleCreatorPresets.ini";

#ifndef BATTLECREATOR_ENABLE_DEATHMATCH_DIAGNOSTICS
#define BATTLECREATOR_ENABLE_DEATHMATCH_DIAGNOSTICS 0
#endif

#ifndef BATTLECREATOR_ENABLE_HEADSHOT_MULTIPLIER_DIAGNOSTICS
#define BATTLECREATOR_ENABLE_HEADSHOT_MULTIPLIER_DIAGNOSTICS 0
#endif

#ifndef BATTLECREATOR_ENABLE_EXECUTION_PREVENTION_DIAGNOSTICS
#define BATTLECREATOR_ENABLE_EXECUTION_PREVENTION_DIAGNOSTICS 1
#endif

enum class BattleType
{
    AllWeapons,
    MeleeOnly,
    NoWeapons
};

enum class BattleMode
{
    Teams,
    FreeForAll,
    TeamDeathmatch,
    FreeForAllDeathmatch
};

enum class PlayerRelation
{
    Friendly,
    Neutral,
    Hostile
};

enum class Difficulty
{
    Easy,
    Medium,
    Hard,
    Extreme,
    Special,
    Bosses
};

enum class ScriptedActionType
{
    None,
    DynamiteThrow,
    BossEvasion,
    Other
};

enum class DynamitePhase
{
    None,
    Equipping,
    ThrowRequested,
    ThrowActive,
    Recovering
};

enum class BossEvasionStyle
{
    None,
    NativeDive,
    Slide,
    MoveAndShootDash
};

enum class BattlePreparationPhase
{
    None,
    SpawningFighters,
    AssigningGroups,
    ApplyingRelationships,
    ApplyingDamagePermissions,
    PreparingFighters,
    StartingCombat,
    Failed
};

enum class BattlePreset
{
    PlayerFight,
    SpectatorDuel,
    FourWayChaos,
    BossShowdown
};

enum class LeaderboardMode
{
    Kills,
    Position
};

enum class DeathmatchRespawnState
{
    None,
    DeathBookkeeping,
    WaitingForCorpseDeletion,
    WaitingForRespawn,
    Queued,
    Spawning,
    Finalising,
    Complete,
    Failed
};

struct Vec3
{
    float x{};
    float y{};
    float z{};
};

struct Settings
{
    DWORD menuKey = VK_F9;
    float firearmSpawnDistance = 26.0f;
    float meleeSpawnDistance = 12.0f;
    float unarmedSpawnDistance = 8.0f;
    float cleanupDistance = 360.0f;
    float combatMoveSpeedMultiplier = 1.08f;
    int maxTeamCount = 20;
    int bossExecutionHealthThreshold = kBossExecutionHealthThreshold;
    int extremeExecutionHealthThreshold = kExtremeExecutionHealthThreshold;
    int bossBlockedExecutionDamage = kBossBlockedExecutionDamage;
    int bossDefensiveHealthThreshold = kBossDefensiveHealthThreshold;
    DWORD bossDodgeDeadEyeSuppressMs = kBossDodgeDeadEyeSuppressMs;
    DWORD npcDeathmatchRespawnDelayMs = kNpcDeathmatchRespawnDelayMs;
    int defaultDeathmatchKillLimit = kDefaultDeathmatchKillLimit;
    int minDeathmatchKillLimit = kMinDeathmatchKillLimit;
    int maxDeathmatchKillLimit = kMaxDeathmatchKillLimit;
    DWORD bossHealGunDelayMs = 12000;
    DWORD bossHealMeleeDelayMs = 14000;
    DWORD bossHealGunTickMs = 5500;
    DWORD bossHealMeleeTickMs = 7000;
    int bossHealAmount = 1;
    DWORD regularHealDelayMs = 3500;
    DWORD regularHealTickMs = 900;
    int regularHealMinAmount = 6;
    bool immediateDeathmatchNpcCorpseCleanup = true;
    DWORD deathmatchCorpseVisibleMs = kDeathmatchCorpseVisibleMs;
    int deathmatchMaximumRespawnsPerFrame = kDeathmatchMaxRespawnsPerFrame;
    DWORD deathmatchMinimumRespawnGapMs = kDeathmatchRespawnGapMs;
    DWORD deathmatchSnapshotRefreshMs = kDeathmatchSnapshotRefreshMs;
    int deathmatchMaximumFullRetargetsPerFrame = kDeathmatchMaxFullRetargetsPerFrame;
    int largeDeathmatchThreshold = kLargeDeathmatchThreshold;
    DWORD largeDeathmatchCombatUpdateMs = kLargeDeathmatchCombatUpdateMs;
    DWORD largeDeathmatchBlipValidationMs = kLargeDeathmatchBlipValidationMs;
    DWORD largeDeathmatchDynamicRepairMs = kLargeDeathmatchDynamicRepairMs;
    DWORD soloFfaIdleCheckMs = kSoloFfaIdleCheckMs;
    DWORD soloFfaIdleThresholdMs = kSoloFfaIdleThresholdMs;
    bool preventPersistentDroppedWeapons = true;
    bool respawnTeamDeathmatchAtOriginalSpawn = false;
    bool enableIdleWatchdog = true;
    DWORD ordinaryIdleCheckIntervalMs = 1800;
    DWORD ordinaryIdleThresholdMs = 4000;
    int ordinaryIdleConsecutiveChecks = 2;
    DWORD idleSoftRecoveryDelayMs = 1200;
    DWORD idleHardRecoveryCooldownMs = 5000;
    float idleRepositionMinDistance = 3.0f;
    float idleRepositionMaxDistance = 6.0f;
    bool idleAllowForcedTargetChange = true;
    bool forcePlayerSpectator = false;
    bool enableManualTeamSpawns = false;
    bool neutralsFriendlyUntilAttacked = false;
    float spectatorMaxTargetDistance = kDefaultSpectatorMaxTargetDistance;
    bool noDeadEyeDuringBattles = false;
    bool neverWantedDuringBattles = true;
    int startCountdownSeconds = 0;
    bool enableCorpseCleanup = true;
    DWORD normalCorpseLifetimeMs = kNormalCorpseMinimumLifetimeMs;
    DWORD eliteCorpseLifetimeMs = kEliteCorpseMinimumLifetimeMs;
    DWORD maximumCorpseLifetimeMs = kMaximumCorpseLifetimeMs;
    DWORD corpseCleanupCheckMs = kCorpseCleanupCheckMs;
    float corpseCleanupMinPlayerDistance = kCorpseCleanupMinPlayerDistance;
    int preferredMaximumCorpses = kPreferredMaximumBattleCorpses;
    int hardMaximumCorpses = kHardMaximumBattleCorpses;
    bool cleanTrackedDroppedWeapons = true;
    bool enableDistantBattleSimulation = true;
    float distantBattleSimulationDistance = kDefaultDistantBattleSimulationDistance;
    DWORD distantBattleSimulationDelayMs = kDefaultDistantBattleSimulationDelayMs;
    DWORD distantBattleSimulationTickMs = kDefaultDistantBattleSimulationTickMs;
};

struct PedSet
{
    const char* name;
    std::array<const char*, 6> models;
    std::array<const char*, 3> firearms;
    std::array<const char*, 3> meleeWeapons;
};

struct BossDef
{
    const char* name;
    std::array<const char*, 5> models;
    const char* voice;
    int outfit = -1;
    float moveRate = 1.0f;
    int health = 500;
    int accuracy = 100;
    int shootRate = 1000;
    DWORD approachDelayMs = 1200;
    DWORD retaskDelayMs = 1800;
    DWORD shootBurstDelayMs = 650;
    int shotDurationMs = 1350;
    int woundedShotDurationMs = 950;
    DWORD coverDelayMs = 6200;
    DWORD woundedCoverDelayMs = 850;
    DWORD evasiveCooldownMs = 3800;
    int slideDiveChanceClose = 68;
    int slideDiveChanceFar = 42;
    int dodgeDeadEyeBlockChance = 50;
};

struct NamedPedDef
{
    const char* name;
    std::array<const char*, 4> models;
    const char* voice;
    int outfit = -1;
};

struct SpecialPedDef
{
    const char* name;
    std::array<const char*, 4> models;
    const char* voice;
    int outfit = -1;
    int health = 300;
    int minAccuracy = 70;
    int maxAccuracy = 90;
    int combatMovement = 2;
    int combatRange = 2;
    int shootRate = 850;
    float moveRate = 1.0f;
    bool meleeSpecialist = false;
    DWORD approachDelayMs = 1800;
    DWORD retaskDelayMs = 2300;
    DWORD shootBurstDelayMs = 1200;
    DWORD coverDelayMs = 9000;
};

struct DifficultyTuning
{
    const char* name;
    int health;
    int minAccuracy;
    int maxAccuracy;
    bool hardened;
    bool heals;
    int combatAbility;
    int combatMovement;
    int combatRange;
    int shootRate;
    float moveRate = 1.0f;
    DWORD approachDelayMs = 2600;
    DWORD retaskDelayMs = 3200;
    DWORD shootBurstDelayMs = 1500;
};

struct TeamRosterSlot
{
    int count = 0;
    int pedSet = 0;
    int boss = 0;
    int special = 0;
    Difficulty difficulty = Difficulty::Easy;
};

struct TeamSetup
{
    PlayerRelation playerRelation = PlayerRelation::Neutral;
    std::vector<TeamRosterSlot> sets;
    bool manualSpawnSet = false;
    Vec3 manualSpawn{};
};

struct Fighter
{
    Ped ped{};
    Blip blip{};
    Hash model{};
    Hash group{};
    Hash combatWeapon{};
    Hash closeWeapon{};
    Hash mediumWeapon{};
    Hash longWeapon{};
    Ped currentTarget{};
    int team = 0;
    int battleRoyaleSquad = -1;
    int battleRoyaleSquadSlot = -1;
    int playerSquadSlot = -1;
    int spawnIndex = 0;
    Vec3 originalSpawn{};
    float originalHeading = 0.0f;
    bool originalSpawnSet = false;
    int pedSet = 0;
    int boss = 0;
    int special = 0;
    int outfitIndex = -1;
    Difficulty difficulty = Difficulty::Easy;
    std::string baseName;
    std::string displayName;
    int maxHealth = 100;
    int lastHealth = 100;
    int kills = 0;
    int deaths = 0;
    int finishPosition = 0;
    DeathmatchRespawnState respawnState = DeathmatchRespawnState::None;
    bool pendingRespawn = false;
    DWORD respawnReadyAt = 0;
    DWORD corpseDeleteAt = 0;
    int respawnAttempts = 0;
    bool hardened = false;
    bool heals = false;
    bool deathRecorded = false;
    bool killedPlayer = false;
    DWORD spawnedAt = 0;
    DWORD respawnAt = 0;
    DWORD lastTask = 0;
    DWORD lastTune = 0;
    DWORD lastDamage = 0;
    DWORD lastHeal = 0;
    DWORD lastPlayerDamage = 0;
    DWORD lastWeaponReady = 0;
    Hash lastWeaponReadyHash{};
    DWORD lastWeaponSwitch = 0;
    Hash pendingCombatWeapon{};
    Ped pendingWeaponTarget{};
    DWORD pendingWeaponSince = 0;
    Hash desiredWeapon{};
    Hash confirmedWeapon{};
    Hash weaponPending{};
    DWORD weaponPendingSince = 0;
    DWORD weaponLastConfirmedAt = 0;
    DWORD weaponSettleUntil = 0;
    int weaponRetryCount = 0;
    Hash rangeWeaponCandidate{};
    Ped rangeWeaponCandidateTarget{};
    DWORD rangeWeaponCandidateSince = 0;
    Hash temporaryWeaponOverride{};
    DWORD temporaryWeaponOverrideUntil = 0;
    DWORD currentTargetStartedAt = 0;
    DWORD lastTargetScan = 0;
    DWORD lastProgressCheck = 0;
    DWORD stuckSince = 0;
    DWORD lastCombatActivityAt = 0;
    DWORD lastIdleRecoveryAt = 0;
    DWORD nextIdleWatchdogCheckAt = 0;
    DWORD lastObservedShotAt = 0;
    DWORD lastObservedMovementAt = 0;
    DWORD lastObservedTargetDamageAt = 0;
    Ped idleWatchdogTarget{};
    Vec3 idleWatchdogPosition{};
    int idleWatchdogTargetHealth = 0;
    int consecutiveIdleChecks = 0;
    int idleRecoveryStage = 0;
    DWORD scriptedActionStartedAt = 0;
    DWORD scriptedActionResumeAt = 0;
    DWORD scriptedActionTimeoutAt = 0;
    ScriptedActionType scriptedActionType = ScriptedActionType::None;
    DynamitePhase dynamitePhase = DynamitePhase::None;
    Hash projectileWeapon{};
    Hash projectileRestoreWeapon{};
    Ped projectileTarget{};
    Vec3 projectileThrowPos{};
    int projectileAmmoBefore = -1;
    bool projectileTaskIssued = false;
    bool projectileTaskObservedActive = false;
    bool projectileReleaseConfirmed = false;
    int projectileTaskRetries = 0;
    DWORD projectileEquipRequestedAt = 0;
    DWORD projectileTaskRequestedAt = 0;
    DWORD projectileCommittedAt = 0;
    DWORD projectileFailureCooldownUntil = 0;
    DWORD nextDynamiteScanAt = 0;
    DWORD nextMaintenanceAt = 0;
    DWORD nextCombatUpdateAt = 0;
    DWORD nextBlipCheckAt = 0;
    DWORD nextDynamicTuneRepairAt = 0;
    DWORD nextGroupValidationAt = 0;
    DWORD lastEvasionEligibilityCheck = 0;
    DWORD lastPlayerDodgeEligibilityCheck = 0;
    Vec3 evasionStartPos{};
    Vec3 evasionTargetPos{};
    BossEvasionStyle evasionStyle = BossEvasionStyle::None;
    bool evasionTaskRequested = false;
    bool evasionActuallyStarted = false;
    bool evasionFinished = false;
    bool evasionDeadEyeSuppressed = false;
    bool evasionShotsObserved = false;
    bool evasionPlayerTriggered = false;
    bool evasionShootDuringDash = true;
    bool evasionVelocityFallbackApplied = false;
    int evasionFallbackAttempts = 0;
    Ped evasionThreat{};
    Ped evasionAimTarget{};
    Ped evasionFiringTarget{};
    float evasionSideX = 0.0f;
    float evasionSideY = 0.0f;
    float evasionBackX = 0.0f;
    float evasionBackY = 0.0f;
    float evasionSideSign = 0.0f;
    float evasionTaskSpeed = 0.0f;
    DWORD evasionDashDurationMs = 0;
    DWORD evasionRequestedAt = 0;
    DWORD evasionStartedAt = 0;
    DWORD evasionExpectedEndAt = 0;
    DWORD evasionDeadEyeBlockStartedAt = 0;
    DWORD evasionDeadEyeBlockUntil = 0;
    DWORD evasionFollowUpAt = 0;
    bool playerAimPressureActive = false;
    DWORD playerAimPressureStartedAt = 0;
    DWORD nextPlayerAimDodgeAllowedAt = 0;
    DWORD nextPlayerThreatDodgeAt = 0;
    DWORD lastPlayerThreatDodgeAt = 0;
    DWORD lastPlayerDamageDodgeAt = 0;
    DWORD lastBlipUpdate = 0;
    int lastBlipRelation = -1;
    DWORD lastShotTask = 0;
    DWORD lastActualShot = 0;
    DWORD lastRepositionTask = 0;
    DWORD lastEvasiveTask = 0;
    DWORD lastDynamiteTask = 0;
    DWORD lastDefensiveTask = 0;
    DWORD lastFollowTask = 0;
    DWORD lastSquadTask = 0;
    DWORD lastSpecialTask = 0;
    DWORD crouchUntil = 0;
    DWORD defensiveCombatStartedAt = 0;
    DWORD defensiveCombatUntil = 0;
    DWORD recentDamageWindowStarted = 0;
    DWORD lastGrappleAttempt = 0;
    DWORD lastGrappleBreak = 0;
    int recentDamageHits = 0;
    int bossBurstsSinceMovement = 0;
    bool wasInCover = false;
    int criticalRevives = 0;
    bool cinematicRecoveryActive = false;
    DWORD cinematicRecoveryStarted = 0;
    DWORD cinematicRecoveryRecoverAt = 0;
    int cinematicRecoveryHealth = 0;
    Hash damageBlockedGroup = 0;
    bool damageBlockedGroupValid = false;
    Hash damagePlayerGroup = 0;
    bool damagePlayerAllowed = true;
    bool damagePlayerPermissionValid = false;
    DWORD diedAt = 0;
    DWORD corpseCleanupEligibleAt = 0;
    DWORD lastCorpseCleanupCheck = 0;
    bool corpseCleanupQueued = false;
    bool corpseDeleted = false;
    Vec3 deathPosition{};
    Object droppedWeaponObject{};
    const char* voiceName = nullptr;
    Vec3 lastProgressPos{};
};

struct BattleCorpse
{
    Ped ped{};
    Object droppedWeaponObject{};
    DWORD diedAt = 0;
    DWORD cleanupEligibleAt = 0;
    DWORD lastCleanupCheck = 0;
    Vec3 position{};
    bool elite = false;
    bool deleted = false;
    int retries = 0;
    int ownerIndex = -1;
};

struct FighterSnapshot
{
    Ped ped{};
    Vec3 position{};
    Hash group{};
    int team = -1;
    int fighterIndex = -1;
    bool alive = false;
    bool targetable = false;
};

struct MenuState
{
    bool open = false;
    int row = 0;
    int team = 0;
    int slot = 0;
    BattlePreset preset = BattlePreset::PlayerFight;
    BattleMode mode = BattleMode::Teams;
    BattleType battleType = BattleType::AllWeapons;
    bool freeForAllSpectate = false;
    int battleRoyaleTeamSize = 1;
    int battleRoyaleSet = 0;
    int killLimit = kDefaultDeathmatchKillLimit;
    int presetSlot = 1;
    bool settingsPage = false;
    TeamRosterSlot battleRoyaleDraft{};
};

struct RuntimeState
{
    bool battleActive = false;
    bool resultAnnounced = false;
    int initialActiveTeams = 0;
    DWORD lastStatusUntil = 0;
    DWORD lastUpdate = 0;
    DWORD nextCleanupDistanceCheck = 0;
    std::string status = "F9 opens Battle Creator";
    Vec3 battleCenter{};
    std::array<Hash, kTeamCount> groups{};
    std::array<bool, kTeamCount> neutralTeamProvokedByPlayer{};
    std::vector<Fighter> fighters;
    std::vector<std::string> leaderboardLines;
    std::vector<std::string> leaderboardKillLines;
    std::vector<std::string> leaderboardPositionLines;
    LeaderboardMode leaderboardMode = LeaderboardMode::Kills;
    int leaderboardTotal = 0;
    int leaderboardKillTotal = 0;
    int leaderboardPositionTotal = 0;
    DWORD leaderboardUntil = 0;
    int playerKills = 0;
    int playerDeaths = 0;
    int playerFinishPosition = 0;
    Ped playerKillerPed = 0;
    std::string playerKillerName;
    bool playerKillerRecorded = false;
    Ped playerRecentDamagerPed = 0;
    DWORD playerRecentDamagerAt = 0;
    int playerLastObservedHealth = 0;
    DWORD playerVitalsRefillUntil = 0;
    DWORD bossDodgeDeadEyeSuppressedUntil = 0;
    DWORD bossDodgeDeadEyeNextAllowedAt = 0;
    Ped bossDodgeDeadEyeLastBoss = 0;
    bool bossDodgeDeadEyeSuppressionActive = false;
    bool noDeadEyeModifierActive = false;
    bool freeForAll = false;
    bool deathmatch = false;
    bool freeForAllSpectate = false;
    int freeForAllTeamSize = 1;
    Hash playerFreeForAllGroup = 0;
    bool playerParticipating = false;
    bool playerWasParticipant = false;
    bool playerEliminated = false;
    bool playerSpectating = false;
    bool playerRevivePending = false;
    bool playerRespawnOverrideActive = false;
    bool playerSafePosValid = false;
    bool playerHiddenForSpectator = false;
    bool wantedSuppressionActive = false;
    bool spectatorCameraActive = false;
    bool spectatorControlOverride = false;
    bool spectatorCameraSmoothed = false;
    bool startCountdownActive = false;
    bool relationshipsDirty = true;
    DWORD lastRelationshipSafetyRefresh = 0;
    DWORD lastRelationshipValidation = 0;
    int previousMaxWantedLevel = 5;
    Cam spectatorCam = 0;
    int spectatorTargetIndex = -1;
    int preferredSpectatorTargetIndex = -1;
    int spectatorCameraLastTargetIndex = -1;
    DWORD startCountdownEndsAt = 0;
    DWORD playerReviveAt = 0;
    DWORD playerScreenRepairUntil = 0;
    Ped playerBattleCorpse = 0;
    Vec3 spectatorCameraPos{};
    Vec3 spectatorCameraLookAt{};
    Vec3 spectatorReturnPos{};
    float spectatorReturnHeading = 0.0f;
    bool spectatorReturnPosValid = false;
    DWORD lastSpectatorPlayerFollowAt = 0;
    Vec3 playerLastSafePos{};
    float playerLastSafeHeading = 0.0f;
    int playerTeam = -1;
    int freeForAllPlayerScatterIndex = -1;
    float freeForAllSpawnAngle = 0.0f;
    Hash freeForAllSpawnGroup = 0;
    std::vector<Hash> freeForAllGroups;
    BattlePreparationPhase preparationPhase = BattlePreparationPhase::None;
    std::vector<int> preparationCombatants;
    std::vector<Hash> preparationGroups;
    int preparationRequestedFighters = 0;
    int preparationSpawnedFighters = 0;
    int preparationExpectedGroups = 0;
    int preparationSetIndex = 0;
    int preparationSetMember = 0;
    int preparationGlobalSpawnIndex = 0;
    int preparationSquadIndex = 0;
    int preparationFighterIndex = 0;
    size_t preparationRelationshipPlayerIndex = 0;
    size_t preparationRelationshipGroupA = 0;
    size_t preparationRelationshipGroupB = 1;
    int preparationRelationshipSettersDone = 0;
    int preparationRelationshipSettersTotal = 0;
    int preparationMaxGroupsPerFrame = 0;
    int preparationMaxRelationshipSettersPerFrame = 0;
    int preparationMaxFightersPerFrame = 0;
    bool preparationGroupCreationFailed = false;
    std::vector<BattleCorpse> battleCorpses;
    std::vector<int> deathmatchRespawnQueue;
    std::vector<FighterSnapshot> fighterSnapshots;
    size_t corpseCleanupCursor = 0;
    size_t detachedCorpseCleanupCursor = 0;
    size_t deathmatchRespawnQueueCursor = 0;
    DWORD nextCorpseCleanupPassAt = 0;
    DWORD nextDeathmatchRespawnAllowedAt = 0;
    DWORD nextFighterSnapshotRefreshAt = 0;
    DWORD nextDeathmatchDiagnosticsAt = 0;
    int deathmatchRespawnsThisFrame = 0;
    int fullRetargetsThisFrame = 0;
    int deathmatchMaxRespawnsInFrame = 0;
    int deathmatchRespawnsCreated = 0;
    int deathmatchRespawnAllocationFailures = 0;
    int deathmatchRetargetsRequested = 0;
    int deathmatchRetargetsProcessed = 0;
    int deathmatchRetargetsDeferred = 0;
    int targetScansUsingSnapshots = 0;
    int targetScansWithoutSnapshots = 0;
    int fighterSnapshotRefreshes = 0;
    int trackedDroppedWeaponsDeleted = 0;
    int corpsesRemoved = 0;
    int corpseDeletionRetries = 0;
    int corpseDeletionFailures = 0;
    int staleTargetReferencesCleared = 0;
    DWORD distantSimulationEligibleSince = 0;
    DWORD nextDistantSimulationAt = 0;
    int simulatedBattleDeaths = 0;
    int protectedExecutionFallbacks = 0;
    std::string compactHudLine1;
    std::string compactHudLine2;
    bool compactHudTwoLine = false;
    DWORD compactHudNextRefreshAt = 0;
};

#if 0
struct BattleCreatorPerfCounters
{
    int liveFighters = 0;
    int activeRelationshipGroups = 0;
    int relationshipSetters = 0;
    int damagePermissionSetters = 0;
    int staticTuningCalls = 0;
    int dynamicTuningRepairs = 0;
    int maintainFighterCalls = 0;
    int taskFighterCalls = 0;
    int targetScans = 0;
    int currentWeaponQueries = 0;
    int blipNativeCalls = 0;
    int dynamiteClusterScans = 0;
    int dynamitePairChecks = 0;
    int failedPedAllocations = 0;
    int failedGroupAllocations = 0;
    int pedsCreated = 0;
    int pedsDeleted = 0;
    int groupsCreated = 0;
    int groupsRemoved = 0;
    int livingBattlePeds = 0;
    int existingDeadBattlePeds = 0;
    int trackedDeathmatchCorpses = 0;
    int eligibleCorpses = 0;
    int corpsesRemoved = 0;
    int deletionRetries = 0;
    int deletionFailures = 0;
    int corpseCountAbovePreferred = 0;
    int corpseCountAboveHard = 0;
    int trackedDroppedWeapons = 0;
    int droppedWeaponsDeleted = 0;
    int staleTargetReferencesCleared = 0;
    int totalExistingBattlePedEntities = 0;
    int totalBattleEntityDeletions = 0;
};
#endif

Settings g_settings;
MenuState g_menu = [] {
    MenuState menu{};
    menu.battleRoyaleDraft.count = 1;
    menu.battleRoyaleDraft.pedSet = 1;
    menu.battleRoyaleDraft.difficulty = Difficulty::Medium;
    return menu;
}();
RuntimeState g_runtime;
std::vector<TeamRosterSlot> g_battleRoyaleSets;
std::array<TeamSetup, kTeamCount> g_teams = [] {
    std::array<TeamSetup, kTeamCount> teams{};
    teams[0].playerRelation = PlayerRelation::Friendly;
    teams[1].playerRelation = PlayerRelation::Hostile;
    teams[2].playerRelation = PlayerRelation::Hostile;
    teams[3].playerRelation = PlayerRelation::Hostile;
    return teams;
}();

int clampDeathmatchKillLimitValue(int value)
{
    if (value <= 0)
        return 0;

    int minLimit = std::max(1, g_settings.minDeathmatchKillLimit);
    int maxLimit = std::max(minLimit, g_settings.maxDeathmatchKillLimit);
    return std::clamp(value, minLimit, maxLimit);
}

Hash joaat(const char* text);
void markRelationshipsDirty();
void updateRelationshipsIfNeeded(DWORD t);
int executionHealthThreshold(const Fighter& fighter);
bool underExecutionHealthThreshold(const Fighter& fighter, int health, bool dead);
bool isAlive(const Fighter& fighter);
int aliveFighterCount();
void clampCurrentSelection();
bool battlePreparationActive();
bool freeForAllSelected();
void clearAllManualTeamSpawns();
bool isUnarmedWeapon(Hash weapon);
bool weaponControllerSettling(const Fighter& fighter, DWORD t);
int bossDodgeDeadEyeBlockChance(const Fighter& fighter);
float kdRatio(int kills, int deaths);
std::string kdText(int kills, int deaths);
int groupKillScore(Hash group);
int groupDeathScore(Hash group);
bool isMobileFireBoss(const Fighter& fighter);
bool isValidEnemyTarget(const Fighter& fighter, Ped candidate);
bool isEnhancedFighter(const Fighter& fighter);
bool taskConvergeTowardDistantTarget(Fighter& fighter, Ped target, DWORD t, float distSq, bool force);
DWORD fighterPhaseOffset(const Fighter& fighter, DWORD interval, DWORD salt);
bool largeDeathmatchActive();
DWORD dynamicTuningRepairInterval();
DWORD fighterBlipValidationInterval();
void resetIdleWatchdogState(Fighter& fighter, DWORD t, Ped target);
bool updateBossEvasionStart(Fighter& fighter, DWORD t);
void recoverFromBossEvasion(Fighter& fighter, DWORD t);
void taskBossAttackBurst(Fighter& fighter, Ped target, DWORD t, bool inCover, bool woundedBoss);
void removeFighterBlip(Fighter& fighter);
void seedFighterUpdateSchedule(Fighter& fighter, DWORD t);
void stopSpectatorCamera();
void updateSpectatorCamera(DWORD t);
void cycleSpectatorCamera();
void selectSpectatorCameraTarget(int direction);
void saveCurrentSettingsToIni(bool showStatus);
void resetPlayerDamageAttribution();

const std::array<PedSet, 12> kDefaultPedSets{{
    {
        "Bounty Hunters",
        { "S_M_M_BOUNTYHUNTER_01", "G_M_M_UNIBOUNTYHUNTER_01", "G_M_M_UNICRIMINALS_01", "S_M_M_DISPATCHLEADERPOLICE_01", "S_M_M_AMBIENTLAWRURAL_01", nullptr },
        { "WEAPON_REPEATER_CARBINE", "WEAPON_RIFLE_BOLTACTION", "WEAPON_REVOLVER_CATTLEMAN" },
        { "WEAPON_MELEE_KNIFE", "WEAPON_MELEE_HATCHET", "WEAPON_MELEE_MACHETE" }
    },
    {
        "O'Driscolls",
        { "G_M_M_UNIDUSTER_01", "G_M_M_UNICRIMINALS_01", "G_M_M_UNIMOUNTAINMEN_01", "G_M_M_UNIRANCHERS_01", "A_M_M_GRIFANCYTRAVELLERS_01", nullptr },
        { "WEAPON_REPEATER_CARBINE", "WEAPON_SHOTGUN_DOUBLEBARREL", "WEAPON_REVOLVER_CATTLEMAN" },
        { "WEAPON_MELEE_KNIFE", "WEAPON_MELEE_HATCHET", "WEAPON_MELEE_MACHETE" }
    },
    {
        "Lawmen",
        { "S_M_M_AMBIENTLAWRURAL_01", "S_M_M_DISPATCHLEADERPOLICE_01", "S_M_M_VALDEPUTY_01", "S_M_M_STRDEPUTY_01", "S_M_M_RHDDEPUTY_01", nullptr },
        { "WEAPON_REPEATER_CARBINE", "WEAPON_REVOLVER_CATTLEMAN", "WEAPON_RIFLE_BOLTACTION" },
        { "WEAPON_MELEE_KNIFE", "WEAPON_MELEE_MACHETE", "WEAPON_MELEE_HATCHET" }
    },
    {
        "Lemoyne Raiders",
        { "G_M_M_UNIRAIDERS_01", "G_M_M_UNICRIMINALS_01", "G_M_M_UNIGRAYS_01", "G_M_M_UNIBRAITHWAITES_01", "A_M_M_BLUROUGHWORKERS_01", nullptr },
        { "WEAPON_REPEATER_CARBINE", "WEAPON_SHOTGUN_DOUBLEBARREL", "WEAPON_REVOLVER_CATTLEMAN" },
        { "WEAPON_MELEE_MACHETE", "WEAPON_MELEE_KNIFE", "WEAPON_MELEE_HATCHET" }
    },
    {
        "Del Lobos",
        { "G_M_M_UNIBANDITOS_01", "G_M_M_UNICRIMINALS_01", "G_M_M_UNIMOUNTAINMEN_01", "A_M_M_ARMCHOLERACORPSE_01", "A_M_M_TUMTOWNFOLK_01", nullptr },
        { "WEAPON_REPEATER_CARBINE", "WEAPON_REVOLVER_CATTLEMAN", "WEAPON_SHOTGUN_SAWEDOFF" },
        { "WEAPON_MELEE_MACHETE", "WEAPON_MELEE_KNIFE", "WEAPON_MELEE_HATCHET" }
    },
    {
        "Murfree Brood",
        { "G_M_M_UNIINBRED_01", "G_M_M_UNIMOUNTAINMEN_01", "G_M_M_UNICRIMINALS_01", "A_M_M_BIVROUGHWORKERS_01", "A_M_M_BIVWORKINGMEN_01", nullptr },
        { "WEAPON_SHOTGUN_DOUBLEBARREL", "WEAPON_REPEATER_CARBINE", "WEAPON_REVOLVER_CATTLEMAN" },
        { "WEAPON_MELEE_MACHETE", "WEAPON_MELEE_KNIFE", "WEAPON_MELEE_HATCHET" }
    },
    {
        "Skinner Brothers",
        { "G_M_M_UNIMOUNTAINMEN_01", "G_M_M_UNICRIMINALS_01", "G_M_M_UNIRANCHERS_01", "A_M_M_TUMTOWNFOLK_01", "A_M_M_ASBTOWNFOLK_01", nullptr },
        { "WEAPON_RIFLE_BOLTACTION", "WEAPON_REPEATER_CARBINE", "WEAPON_SHOTGUN_DOUBLEBARREL" },
        { "WEAPON_MELEE_HATCHET", "WEAPON_MELEE_MACHETE", "WEAPON_MELEE_KNIFE" }
    },
    {
        "Night Folk",
        { "G_M_M_UNICRIMINALS_01", "G_M_M_UNIINBRED_01", "A_M_M_BIVROUGHWORKERS_01", "A_M_M_BIVWORKINGMEN_01", "A_M_M_LAGTOWNFOLK_01", nullptr },
        { "WEAPON_SHOTGUN_DOUBLEBARREL", "WEAPON_REPEATER_CARBINE", "WEAPON_REVOLVER_CATTLEMAN" },
        { "WEAPON_MELEE_MACHETE", "WEAPON_MELEE_KNIFE", "WEAPON_MELEE_HATCHET" }
    },
    {
        "Pinkertons",
        { "S_M_M_PINLAW_01", "S_M_M_AMBIENTLAWRURAL_01", "S_M_M_DISPATCHLEADERPOLICE_01", "G_M_M_UNICORNWALLGOONS_01", "S_M_M_VALDEPUTY_01", nullptr },
        { "WEAPON_RIFLE_BOLTACTION", "WEAPON_REPEATER_CARBINE", "WEAPON_REVOLVER_CATTLEMAN" },
        { "WEAPON_MELEE_KNIFE", "WEAPON_MELEE_MACHETE", "WEAPON_MELEE_HATCHET" }
    },
    {
        "Army",
        { "S_M_M_ARMY_01", "S_M_Y_ARMY_01", "G_M_M_UNICORNWALLGOONS_01", "S_M_M_AMBIENTLAWRURAL_01", "G_M_M_UNICRIMINALS_01", nullptr },
        { "WEAPON_RIFLE_BOLTACTION", "WEAPON_REPEATER_CARBINE", "WEAPON_REVOLVER_CATTLEMAN" },
        { "WEAPON_MELEE_KNIFE", "WEAPON_MELEE_HATCHET", "WEAPON_MELEE_MACHETE" }
    },
    {
        "Van der Linde Gang",
        { "CS_HOSEAMATTHEWS", "CS_LENNY", "CS_SEAN", "CS_KIERAN", "CS_MRSADLER", nullptr },
        { "WEAPON_REPEATER_CARBINE", "WEAPON_REVOLVER_CATTLEMAN", "WEAPON_SHOTGUN_DOUBLEBARREL" },
        { "WEAPON_MELEE_KNIFE", "WEAPON_MELEE_MACHETE", "WEAPON_MELEE_HATCHET" }
    },
    {
        "Micah's Gang",
        { "CS_CLEET", "CS_JOE", "G_M_M_UNIDUSTER_01", "G_M_M_UNIDUSTER_02", "G_M_M_UNIDUSTER_03", nullptr },
        { "WEAPON_REPEATER_CARBINE", "WEAPON_REVOLVER_CATTLEMAN", "WEAPON_SHOTGUN_DOUBLEBARREL" },
        { "WEAPON_MELEE_KNIFE", "WEAPON_MELEE_MACHETE", "WEAPON_MELEE_HATCHET" }
    }
}};

std::vector<PedSet> g_pedSets(kDefaultPedSets.begin(), kDefaultPedSets.end());
std::vector<char*> g_customPedSetStrings;

std::array<BossDef, 5> kBosses{{
    { "John Marston", { "CS_JOHNMARSTON", "CS_JOHNMARSTON_REV", "A_M_M_VALTOWNFOLK_01", nullptr, nullptr }, "JOHN_PLAYER", 18, 1.30f, 500, 100, 3950, 650, 650, 160, 1850, 1000, 4800, 850, 5200, 100, 100, 100 },
    { "Dutch Van Der Linde", { "CS_DUTCH", "CS_DUTCHVANDERLINDE", "CS_DUTCH_02", "U_M_M_STORY_DUTCH", nullptr }, "DUTCH", 5, 1.0f, 500, 100, 1120, 1450, 1650, 850, 1250, 950, 1350, 850, 9200, 8, 3, 28 },
    { "Micah Bell", { "CS_MICAH_BELL", "CS_MICAHBELL", "CS_MICAH", "U_M_M_STORY_MICAH", nullptr }, "MICAH", 21, 1.08f, 500, 100, 2600, 650, 850, 260, 2850, 1100, 13200, 1100, 5600, 46, 28, 100 },
    { "Colm O'Driscoll", { "CS_COLMODRISCOLL", "CS_COLM_ODRISCOLL", "U_M_M_STORY_COLM", "G_M_M_UNIDUSTER_01", nullptr }, "COLM", 3, 1.0f, 500, 100, 1380, 1250, 1350, 620, 1350, 950, 1750, 850, 6900, 22, 12, 45 },
    { "Arthur Morgan", { "PLAYER_ZERO", nullptr, nullptr, nullptr, nullptr }, "ARTHUR", 0, 1.30f, 600, 100, 3950, 650, 650, 160, 1850, 1000, 4800, 850, 5200, 100, 100, 100 }
}};

const std::array<NamedPedDef, 5> kNamedGangPeds{{
    { "Hosea Matthews", { "CS_HOSEAMATTHEWS", "CS_HOSEA", "U_M_M_STORY_HOSEA", nullptr }, "HOSEA", 3 },
    { "Lenny Summers", { "CS_LENNY", "CS_LENNYSUMMERS", "U_M_M_STORY_LENNY", nullptr }, "LENNY", 8 },
    { "Sean MacGuire", { "CS_SEAN", "CS_SEANMACGUIRE", "U_M_M_STORY_SEAN", nullptr }, "SEAN", 0 },
    { "Kieran Duffy", { "CS_KIERAN", "CS_KIERANDUFFY", "U_M_M_STORY_KIERAN", nullptr }, "KIERAN", 7 },
    { "Sadie Adler", { "CS_MRSADLER", "CS_SADIEADLER", "CS_SADIE_ADLER", "U_F_M_STORY_SADIE" }, "SADIE", 20 }
}};

const std::array<NamedPedDef, 5> kMicahsGangPeds{{
    { "Cleet", { "CS_CLEET", nullptr, nullptr, nullptr }, nullptr, -1 },
    { "Joe", { "CS_JOE", nullptr, nullptr, nullptr }, nullptr, -1 },
    { "Micah Gunman 1", { "G_M_M_UNIDUSTER_01", "G_M_M_UNICRIMINALS_01", nullptr, nullptr }, nullptr, -1 },
    { "Micah Gunman 2", { "G_M_M_UNIDUSTER_02", "G_M_M_UNICRIMINALS_02", nullptr, nullptr }, nullptr, -1 },
    { "Micah Gunman 3", { "G_M_M_UNIDUSTER_03", "G_M_M_UNIBANDITOS_01", nullptr, nullptr }, nullptr, -1 }
}};

std::array<SpecialPedDef, 4> kSpecialPeds{{
    { "Javier Escuella", { "CS_JAVIERESCUELLA", "CS_JAVIER_ESCUELLA", "U_M_M_STORY_JAVIERESCUELLA", nullptr }, "JAVIER", 1, 245, 88, 100, 3, 2, 1380, 1.48f, false, 700, 900, 390, 5200 },
    { "Bill Williamson", { "CS_BILLWILLIAMSON", "CS_BILL_WILLIAMSON", "U_M_M_STORY_BILLWILLIAMSON", nullptr }, "BILL", 12, 430, 55, 72, 1, 1, 760, 1.0f, true, 1800, 2300, 1200, 8200 },
    { "Tommy", { "CS_MUD2BIGGUY", "U_M_M_STORY_MUD2BIGGUY", nullptr, nullptr }, nullptr, 1, 450, 45, 60, 3, 0, 760, 1.18f, true, 520, 850, 900, 7800 },
    { "Charles Smith", { "CS_CHARLESSMITH", "CS_CHARLES_SMITH", "U_M_M_STORY_CHARLESSMITH", nullptr }, "CHARLES", 1, 460, 94, 100, 3, 2, 1300, 1.16f, true, 850, 1050, 520, 4300 }
}};

std::array<DifficultyTuning, 6> kDifficulty{{
    { "Easy", 60, 10, 30, false, false, 0, 1, 0, 250, 0.96f, 2700, 3600, 1900 },
    { "Medium", 100, 30, 50, false, false, 1, 2, 0, 450, 1.04f, 2100, 2800, 1300 },
    { "Hard", 180, 50, 70, false, false, 2, 3, 1, 650, 1.12f, 1600, 2200, 900 },
    { "Extreme", 300, 85, 100, true, false, 2, 3, 1, 900, 1.14f, 1200, 1800, 700 },
    { "Special", 300, 70, 90, true, false, 2, 3, 1, 850, 1.08f, 1500, 2000, 950 },
    { "Bosses", 500, 100, 100, true, true, 2, 3, 1, 1000, 1.05f, 1000, 1500, 550 }
}};

const std::array<const char*, 6> kDifficultyIniSections{{
    "Difficulty.Easy",
    "Difficulty.Medium",
    "Difficulty.Hard",
    "Difficulty.Extreme",
    "Difficulty.Special",
    "Difficulty.Bosses"
}};

const std::array<const char*, 5> kBossIniSections{{
    "Boss.JohnMarston",
    "Boss.DutchVanDerLinde",
    "Boss.MicahBell",
    "Boss.ColmODriscoll",
    "Boss.ArthurMorgan"
}};

const std::array<const char*, 4> kSpecialIniSections{{
    "Special.JavierEscuella",
    "Special.BillWilliamson",
    "Special.Tommy",
    "Special.CharlesSmith"
}};

std::string leaderboardBaseName(const TeamRosterSlot& slot)
{
    if (slot.difficulty == Difficulty::Bosses)
        return kBosses[static_cast<size_t>(slot.boss)].name;
    if (slot.difficulty == Difficulty::Special)
        return kSpecialPeds[static_cast<size_t>(slot.special)].name;

    switch (slot.pedSet)
    {
    case 0:
        return "Bounty Hunter";
    case 1:
        return "O'Driscoll";
    case 2:
        return "Lawman";
    case 3:
        return "Lemoyne Raider";
    case 4:
        return "Del Lobo";
    case 5:
        return "Murfree";
    case 6:
        return "Skinner";
    case 7:
        return "Night Folk";
    case 8:
        return "Pinkerton";
    case 9:
        return "Soldier";
    case kNamedGangPedSetIndex:
        return "Van der Linde";
    case kMicahsGangPedSetIndex:
        return "Micah's Gang";
    default:
        return g_pedSets[static_cast<size_t>(slot.pedSet)].name;
    }
}

std::string leaderboardBaseNameForSpawn(const TeamRosterSlot& slot, const NamedPedDef* namedPed)
{
    if (slot.difficulty != Difficulty::Bosses &&
        slot.difficulty != Difficulty::Special &&
        namedPed &&
        namedPed->name &&
        *namedPed->name)
    {
        return namedPed->name;
    }
    return leaderboardBaseName(slot);
}

std::string nextFighterDisplayName(const std::string& base, bool boss)
{
    int occurrence = 1;
    for (const Fighter& fighter : g_runtime.fighters)
    {
        if (fighter.baseName == base)
            ++occurrence;
    }

    if (boss && occurrence == 1)
        return base;
    return base + "(" + std::to_string(occurrence) + ")";
}

std::string playerLeaderboardName()
{
    Ped player = PLAYER::PLAYER_PED_ID();
    if (!player || !ENTITY::DOES_ENTITY_EXIST(player))
        return "Player";

    Hash model = ENTITY::GET_ENTITY_MODEL(player);
    if (model == joaat("PLAYER_THREE"))
        return "John (Player)";
    if (model == joaat("PLAYER_ZERO"))
        return "Arthur Morgan";
    return "Player";
}

const char* battleTypeName(BattleType type)
{
    switch (type)
    {
    case BattleType::AllWeapons:
        return "All Weapons";
    case BattleType::MeleeOnly:
        return "Melee Only";
    case BattleType::NoWeapons:
        return "No Weapons";
    }
    return "All Weapons";
}

const char* battleModeName(BattleMode mode)
{
    switch (mode)
    {
    case BattleMode::Teams:
        return "Team Survival";
    case BattleMode::FreeForAll:
        return "Battle Royale";
    case BattleMode::TeamDeathmatch:
        return "Team Deathmatch";
    case BattleMode::FreeForAllDeathmatch:
        return "Free For All";
    }
    return "Team Survival";
}

bool freeForAllMode(BattleMode mode)
{
    return mode == BattleMode::FreeForAll || mode == BattleMode::FreeForAllDeathmatch;
}

bool deathmatchMode(BattleMode mode)
{
    return mode == BattleMode::TeamDeathmatch || mode == BattleMode::FreeForAllDeathmatch;
}

const char* freeForAllPlayerName(bool spectate)
{
    return spectate ? "Spectate" : "Play";
}

const char* leaderboardModeName(LeaderboardMode mode)
{
    bool pointMode = g_runtime.deathmatch || deathmatchMode(g_menu.mode);
    bool ffaMode = g_runtime.freeForAll || freeForAllMode(g_menu.mode);
    bool squadFfa = pointMode && ffaMode && (g_runtime.freeForAllTeamSize > 1 || g_menu.battleRoyaleTeamSize > 1);
    switch (mode)
    {
    case LeaderboardMode::Kills:
        return "Kills";
    case LeaderboardMode::Position:
        if (pointMode && !ffaMode)
            return "Teams";
        if (squadFfa)
            return "Squads";
        if (pointMode && ffaMode)
            return "KD";
        return "Position";
    }
    return "Kills";
}

const char* battleRoyaleTeamSizeName(int size)
{
    switch (std::clamp(size, 1, 4))
    {
    case 1:
        return "Solo";
    case 2:
        return "Duo";
    case 3:
        return "Trios";
    case 4:
        return "Squad";
    }
    return "Solo";
}

const char* relationName(PlayerRelation relation)
{
    switch (relation)
    {
    case PlayerRelation::Friendly:
        return "Friendly";
    case PlayerRelation::Neutral:
        return "Neutral";
    case PlayerRelation::Hostile:
        return "Hostile";
    }
    return "Neutral";
}

int difficultyIndex(Difficulty difficulty)
{
    return static_cast<int>(difficulty);
}

const char* difficultyName(Difficulty difficulty)
{
    return kDifficulty[static_cast<size_t>(difficultyIndex(difficulty))].name;
}

const char* presetName(BattlePreset preset)
{
    switch (preset)
    {
    case BattlePreset::PlayerFight:
        return "Player Fight";
    case BattlePreset::SpectatorDuel:
        return "Spectator Duel";
    case BattlePreset::FourWayChaos:
        return "Four-Way Chaos";
    case BattlePreset::BossShowdown:
        return "Boss Showdown";
    }
    return "Player Fight";
}

TeamRosterSlot& selectedSlot()
{
    return g_menu.battleRoyaleDraft;
}

const TeamRosterSlot& selectedSlotConst()
{
    return g_menu.battleRoyaleDraft;
}

bool isUniqueNamedPedSet(int pedSet)
{
    return pedSet == kNamedGangPedSetIndex || pedSet == kMicahsGangPedSetIndex;
}

size_t uniqueNamedPedSetSize(int pedSet)
{
    if (pedSet == kMicahsGangPedSetIndex)
        return kMicahsGangPeds.size();
    if (pedSet == kNamedGangPedSetIndex)
        return kNamedGangPeds.size();
    return 0;
}

const NamedPedDef& uniqueNamedPedForSet(int pedSet, size_t index)
{
    if (pedSet == kMicahsGangPedSetIndex)
        return kMicahsGangPeds[index];
    return kNamedGangPeds[index];
}

int maxCountForSlot(const TeamRosterSlot& slot)
{
    if (slot.difficulty == Difficulty::Bosses || slot.difficulty == Difficulty::Special)
        return 1;
    if (isUniqueNamedPedSet(slot.pedSet))
        return static_cast<int>(uniqueNamedPedSetSize(slot.pedSet));
    return g_settings.maxTeamCount;
}

int effectiveSlotCount(const TeamRosterSlot& slot)
{
    if (slot.count <= 0)
        return 0;
    return std::min(slot.count, maxCountForSlot(slot));
}

bool teamEnabled(const TeamSetup& team)
{
    for (const TeamRosterSlot& slot : team.sets)
    {
        if (effectiveSlotCount(slot) > 0)
            return true;
    }
    return false;
}

DWORD now()
{
    return GetTickCount();
}

Hash joaat(const char* text)
{
    unsigned int hash = 0;
    while (*text)
    {
        char c = *text++;
        if (c >= 'A' && c <= 'Z')
            c += 'a' - 'A';
        hash += static_cast<unsigned char>(c);
        hash += hash << 10;
        hash ^= hash >> 6;
    }
    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;
    return hash;
}

bool keyPressed(DWORD key)
{
    static std::array<SHORT, 256> previous{};
    if (key >= previous.size())
        return false;

    SHORT current = GetAsyncKeyState(key);
    bool pressed = (current & 0x8000) && !(previous[key] & 0x8000);
    previous[key] = current;
    return pressed;
}

bool keyRepeated(DWORD key, DWORD initialDelayMs = kMenuInputRepeatInitialMs, DWORD repeatDelayMs = kMenuInputRepeatMs)
{
    struct RepeatState
    {
        bool down = false;
        DWORD nextRepeatAt = 0;
    };

    static std::array<RepeatState, 256> states{};
    if (key >= states.size())
        return false;

    bool down = (GetAsyncKeyState(key) & 0x8000) != 0;
    RepeatState& state = states[key];
    DWORD t = now();

    if (!down)
    {
        state = {};
        return false;
    }

    if (!state.down)
    {
        state.down = true;
        state.nextRepeatAt = t + initialDelayMs;
        return true;
    }

    if (t < state.nextRepeatAt)
        return false;

    state.nextRepeatAt = t + repeatDelayMs;
    return true;
}

DWORD parseKey(const char* value, DWORD fallback)
{
    if (!value || !*value)
        return fallback;

    if ((value[0] == 'F' || value[0] == 'f') && value[1] >= '1' && value[1] <= '9')
    {
        int number = std::atoi(value + 1);
        if (number >= 1 && number <= 12)
            return VK_F1 + number - 1;
    }

    if (value[1] == '\0')
    {
        char c = value[0];
        if (c >= 'a' && c <= 'z')
            c -= 'a' - 'A';
        return static_cast<DWORD>(c);
    }

    return fallback;
}

std::string readProfileString(const char* path, const char* section, const char* key, const char* fallback, DWORD bufferSize = 512)
{
    std::vector<char> buffer(static_cast<size_t>(std::max<DWORD>(bufferSize, 32u)), '\0');
    GetPrivateProfileStringA(section, key, fallback, buffer.data(), static_cast<DWORD>(buffer.size()), path);
    return buffer.data();
}

bool profileKeyExists(const char* path, const char* section, const char* key)
{
    constexpr const char* missing = "__BATTLE_CREATOR_MISSING_KEY__";
    return readProfileString(path, section, key, missing) != missing;
}

int readProfileInt(const char* path, const char* section, const char* key, int fallback)
{
    return GetPrivateProfileIntA(section, key, fallback, path);
}

std::string readIniString(const char* section, const char* key, const char* fallback)
{
    std::string buffer = readProfileString(kBattleCreatorIni, section, key, fallback);
    return buffer;
}

int readIniInt(const char* section, const char* key, int fallback)
{
    return readProfileInt(kBattleCreatorIni, section, key, fallback);
}

void writeIniString(const char* section, const char* key, const std::string& value)
{
    WritePrivateProfileStringA(section, key, value.c_str(), kBattleCreatorIni);
}

void flushBattleCreatorIni()
{
    WritePrivateProfileStringA(nullptr, nullptr, nullptr, kBattleCreatorIni);
}

void writeIniInt(const char* section, const char* key, int value)
{
    char buffer[32]{};
    std::snprintf(buffer, sizeof(buffer), "%d", value);
    writeIniString(section, key, buffer);
}

void writeIniFloat(const char* section, const char* key, float value)
{
    char buffer[32]{};
    std::snprintf(buffer, sizeof(buffer), "%.2f", value);
    writeIniString(section, key, buffer);
}

float readIniFloat(const char* section, const char* key, float fallback)
{
    std::string value = readIniString(section, key, "");
    if (value.empty())
        return fallback;
    return static_cast<float>(std::atof(value.c_str()));
}

std::string readPresetString(const char* section, const char* key, const char* fallback)
{
    char buffer[128]{};
    GetPrivateProfileStringA(section, key, fallback, buffer, sizeof(buffer), kBattleCreatorPresetsIni);
    return buffer;
}

int readPresetInt(const char* section, const char* key, int fallback)
{
    return GetPrivateProfileIntA(section, key, fallback, kBattleCreatorPresetsIni);
}

void writePresetString(const char* section, const char* key, const std::string& value)
{
    WritePrivateProfileStringA(section, key, value.c_str(), kBattleCreatorPresetsIni);
}

void flushBattleCreatorPresetsIni()
{
    WritePrivateProfileStringA(nullptr, nullptr, nullptr, kBattleCreatorPresetsIni);
}

void writePresetInt(const char* section, const char* key, int value)
{
    char buffer[32]{};
    std::snprintf(buffer, sizeof(buffer), "%d", value);
    WritePrivateProfileStringA(section, key, buffer, kBattleCreatorPresetsIni);
}

void writePresetFloat(const char* section, const char* key, float value)
{
    char buffer[32]{};
    std::snprintf(buffer, sizeof(buffer), "%.2f", value);
    writePresetString(section, key, buffer);
}

float readPresetFloat(const char* section, const char* key, float fallback)
{
    std::string value = readPresetString(section, key, "");
    if (value.empty())
        return fallback;
    return static_cast<float>(std::atof(value.c_str()));
}

bool readIniBool(const char* section, const char* key, bool fallback)
{
    std::string value = readIniString(section, key, fallback ? "true" : "false");
    for (char& c : value)
    {
        if (c >= 'A' && c <= 'Z')
            c = static_cast<char>(c - 'A' + 'a');
    }

    return value == "1" ||
        value == "true" ||
        value == "yes" ||
        value == "on";
}

int readIniClampedInt(const char* section, const char* key, int fallback, int minValue, int maxValue)
{
    return std::clamp(readIniInt(section, key, fallback), minValue, maxValue);
}

int readProfileClampedInt(const char* path, const char* section, const char* key, int fallback, int minValue, int maxValue)
{
    return std::clamp(readProfileInt(path, section, key, fallback), minValue, maxValue);
}

DWORD readIniClampedDword(const char* section, const char* key, DWORD fallback, DWORD minValue, DWORD maxValue)
{
    int value = readIniInt(section, key, static_cast<int>(fallback));
    return static_cast<DWORD>(std::clamp(value, static_cast<int>(minValue), static_cast<int>(maxValue)));
}

float readIniClampedFloat(const char* section, const char* key, float fallback, float minValue, float maxValue)
{
    return std::clamp(readIniFloat(section, key, fallback), minValue, maxValue);
}

std::string trimCopy(const std::string& value)
{
    size_t first = 0;
    while (first < value.size() && std::isspace(static_cast<unsigned char>(value[first])))
        ++first;

    size_t last = value.size();
    while (last > first && std::isspace(static_cast<unsigned char>(value[last - 1])))
        --last;

    return value.substr(first, last - first);
}

std::vector<std::string> splitIniList(const std::string& value)
{
    std::vector<std::string> items;
    size_t start = 0;
    while (start <= value.size())
    {
        size_t comma = value.find(',', start);
        std::string item = trimCopy(value.substr(start, comma == std::string::npos ? std::string::npos : comma - start));
        if (!item.empty())
            items.push_back(item);

        if (comma == std::string::npos)
            break;
        start = comma + 1;
    }
    return items;
}

const char* storeCustomString(const std::string& value)
{
    char* copy = _strdup(value.c_str());
    if (copy)
        g_customPedSetStrings.push_back(copy);
    return copy ? copy : "";
}

template <size_t N>
void fillCustomStringArray(std::array<const char*, N>& output, const std::vector<std::string>& values)
{
    output.fill(nullptr);
    size_t count = std::min(output.size(), values.size());
    for (size_t i = 0; i < count; ++i)
        output[i] = storeCustomString(values[i]);
}

void loadCustomPedSets()
{
    for (char* value : g_customPedSetStrings)
        std::free(value);
    g_customPedSetStrings.clear();
    g_pedSets.assign(kDefaultPedSets.begin(), kDefaultPedSets.end());

    // Prefer the split-out file, but keep legacy main-INI custom sets alive during upgrades.
    int customFileCount = profileKeyExists(kBattleCreatorCustomPedsIni, "CustomPedSets", "Count") ?
        readProfileClampedInt(kBattleCreatorCustomPedsIni, "CustomPedSets", "Count", 0, 0, 64) :
        0;
    int legacyMainIniCount = readProfileClampedInt(kBattleCreatorIni, "CustomPedSets", "Count", 0, 0, 64);
    bool useCustomFile = customFileCount > 0 || legacyMainIniCount <= 0;
    const char* customPedIni = useCustomFile ? kBattleCreatorCustomPedsIni : kBattleCreatorIni;
    int count = useCustomFile ? customFileCount : legacyMainIniCount;
    for (int i = 1; i <= count; ++i)
    {
        std::string section = "CustomPedSet." + std::to_string(i);
        std::string name = trimCopy(readProfileString(customPedIni, section.c_str(), "Name", ""));
        std::vector<std::string> models = splitIniList(readProfileString(customPedIni, section.c_str(), "Models", ""));
        if (name.empty() || models.empty())
            continue;

        std::vector<std::string> firearms = splitIniList(readProfileString(customPedIni, section.c_str(), "Firearms", ""));
        if (firearms.empty())
        {
            firearms.push_back("WEAPON_REVOLVER_CATTLEMAN");
            firearms.push_back("WEAPON_REPEATER_CARBINE");
            firearms.push_back("WEAPON_RIFLE_BOLTACTION");
        }

        std::vector<std::string> meleeWeapons = splitIniList(readProfileString(customPedIni, section.c_str(), "MeleeWeapons", ""));
        if (meleeWeapons.empty())
        {
            meleeWeapons.push_back("WEAPON_MELEE_KNIFE");
            meleeWeapons.push_back("WEAPON_MELEE_HATCHET");
            meleeWeapons.push_back("WEAPON_MELEE_MACHETE");
        }

        PedSet set{};
        set.name = storeCustomString(name);
        fillCustomStringArray(set.models, models);
        fillCustomStringArray(set.firearms, firearms);
        fillCustomStringArray(set.meleeWeapons, meleeWeapons);
        g_pedSets.push_back(set);
    }
}

void normalizeAccuracyRange(int& minAccuracy, int& maxAccuracy)
{
    minAccuracy = std::clamp(minAccuracy, 0, 100);
    maxAccuracy = std::clamp(maxAccuracy, 0, 100);
    if (minAccuracy > maxAccuracy)
        std::swap(minAccuracy, maxAccuracy);
}

void loadDifficultyTuning(const char* section, DifficultyTuning& tuning)
{
    tuning.health = readIniClampedInt(section, "Health", tuning.health, 1, 5000);
    tuning.minAccuracy = readIniClampedInt(section, "MinAccuracy", tuning.minAccuracy, 0, 100);
    tuning.maxAccuracy = readIniClampedInt(section, "MaxAccuracy", tuning.maxAccuracy, 0, 100);
    normalizeAccuracyRange(tuning.minAccuracy, tuning.maxAccuracy);
    tuning.shootRate = readIniClampedInt(section, "ShootRate", tuning.shootRate, 0, 5000);
    tuning.moveRate = readIniClampedFloat(section, "MoveRate", tuning.moveRate, 0.1f, 5.0f);
    tuning.combatAbility = readIniClampedInt(section, "CombatAbility", tuning.combatAbility, 0, 2);
    tuning.combatMovement = readIniClampedInt(section, "CombatMovement", tuning.combatMovement, 0, 3);
    tuning.combatRange = readIniClampedInt(section, "CombatRange", tuning.combatRange, 0, 3);
    tuning.hardened = readIniBool(section, "Hardened", tuning.hardened);
    tuning.heals = readIniBool(section, "Heals", tuning.heals);
    tuning.approachDelayMs = readIniClampedDword(section, "ApproachDelayMs", tuning.approachDelayMs, 100, 30000);
    tuning.retaskDelayMs = readIniClampedDword(section, "RetaskDelayMs", tuning.retaskDelayMs, 100, 30000);
    tuning.shootBurstDelayMs = readIniClampedDword(section, "ShootBurstDelayMs", tuning.shootBurstDelayMs, 50, 30000);
}

void loadBossTuning(const char* section, BossDef& boss)
{
    boss.outfit = readIniClampedInt(section, "Outfit", boss.outfit, -1, 255);
    boss.health = readIniClampedInt(section, "Health", boss.health, 1, 10000);
    boss.accuracy = readIniClampedInt(section, "Accuracy", boss.accuracy, 0, 100);
    boss.shootRate = readIniClampedInt(section, "ShootRate", boss.shootRate, 0, 8000);
    boss.moveRate = readIniClampedFloat(section, "MoveRate", boss.moveRate, 0.1f, 5.0f);
    boss.approachDelayMs = readIniClampedDword(section, "ApproachDelayMs", boss.approachDelayMs, 100, 30000);
    boss.retaskDelayMs = readIniClampedDword(section, "RetaskDelayMs", boss.retaskDelayMs, 100, 30000);
    boss.shootBurstDelayMs = readIniClampedDword(section, "ShootBurstDelayMs", boss.shootBurstDelayMs, 50, 30000);
    boss.shotDurationMs = readIniClampedInt(section, "ShotDurationMs", boss.shotDurationMs, 100, 10000);
    boss.woundedShotDurationMs = readIniClampedInt(section, "WoundedShotDurationMs", boss.woundedShotDurationMs, 100, 10000);
    boss.coverDelayMs = readIniClampedDword(section, "CoverDelayMs", boss.coverDelayMs, 100, 60000);
    boss.woundedCoverDelayMs = readIniClampedDword(section, "WoundedCoverDelayMs", boss.woundedCoverDelayMs, 100, 60000);
    boss.evasiveCooldownMs = readIniClampedDword(section, "EvasiveCooldownMs", boss.evasiveCooldownMs, 100, 60000);
    boss.slideDiveChanceClose = readIniClampedInt(section, "SlideDiveChanceClose", boss.slideDiveChanceClose, 0, 100);
    boss.slideDiveChanceFar = readIniClampedInt(section, "SlideDiveChanceFar", boss.slideDiveChanceFar, 0, 100);
    boss.dodgeDeadEyeBlockChance = readIniClampedInt(section, "DodgeDeadEyeBlockChance", boss.dodgeDeadEyeBlockChance, 0, 100);
}

void loadSpecialTuning(const char* section, SpecialPedDef& special)
{
    special.outfit = readIniClampedInt(section, "Outfit", special.outfit, -1, 255);
    special.health = readIniClampedInt(section, "Health", special.health, 1, 10000);
    special.minAccuracy = readIniClampedInt(section, "MinAccuracy", special.minAccuracy, 0, 100);
    special.maxAccuracy = readIniClampedInt(section, "MaxAccuracy", special.maxAccuracy, 0, 100);
    normalizeAccuracyRange(special.minAccuracy, special.maxAccuracy);
    special.shootRate = readIniClampedInt(section, "ShootRate", special.shootRate, 0, 8000);
    special.moveRate = readIniClampedFloat(section, "MoveRate", special.moveRate, 0.1f, 5.0f);
    special.combatMovement = readIniClampedInt(section, "CombatMovement", special.combatMovement, 0, 3);
    special.combatRange = readIniClampedInt(section, "CombatRange", special.combatRange, 0, 3);
    special.meleeSpecialist = readIniBool(section, "MeleeSpecialist", special.meleeSpecialist);
    special.approachDelayMs = readIniClampedDword(section, "ApproachDelayMs", special.approachDelayMs, 100, 30000);
    special.retaskDelayMs = readIniClampedDword(section, "RetaskDelayMs", special.retaskDelayMs, 100, 30000);
    special.shootBurstDelayMs = readIniClampedDword(section, "ShootBurstDelayMs", special.shootBurstDelayMs, 50, 30000);
    special.coverDelayMs = readIniClampedDword(section, "CoverDelayMs", special.coverDelayMs, 100, 60000);
}

void loadSettings()
{
    g_settings.menuKey = parseKey(readIniString("Keys", "Menu", "F9").c_str(), VK_F9);
    g_settings.firearmSpawnDistance = std::clamp(readIniFloat("Battle", "FirearmSpawnDistance", 26.0f), 2.0f, kMaxBattleSpawnDistance);
    g_settings.meleeSpawnDistance = std::clamp(readIniFloat("Battle", "MeleeSpawnDistance", 12.0f), 2.0f, kMaxBattleSpawnDistance);
    g_settings.unarmedSpawnDistance = std::clamp(readIniFloat("Battle", "UnarmedSpawnDistance", 8.0f), 2.0f, kMaxBattleSpawnDistance);
    g_settings.cleanupDistance = std::clamp(readIniFloat("Battle", "CleanupDistance", 360.0f), 120.0f, 900.0f);
    g_settings.combatMoveSpeedMultiplier = readIniClampedFloat("Battle", "CombatMoveSpeedMultiplier", g_settings.combatMoveSpeedMultiplier, 0.5f, 2.0f);
    g_settings.maxTeamCount = std::clamp(readIniInt("Battle", "MaxTeamCount", 20), 1, 40);
    loadCustomPedSets();
    g_settings.forcePlayerSpectator = readIniBool("BattleModifiers", "ForcePlayerSpectator", g_settings.forcePlayerSpectator);
    g_settings.enableManualTeamSpawns = readIniBool("BattleModifiers", "EnableManualTeamSpawns", g_settings.enableManualTeamSpawns);
    g_settings.neutralsFriendlyUntilAttacked = readIniBool("BattleModifiers", "NeutralsFriendlyUntilAttacked", g_settings.neutralsFriendlyUntilAttacked);
    g_settings.spectatorMaxTargetDistance = readIniClampedFloat("BattleModifiers", "SpectatorMaxTargetDistance", g_settings.spectatorMaxTargetDistance, 0.0f, 500.0f);
    g_settings.noDeadEyeDuringBattles = readIniBool("BattleModifiers", "NoDeadEyeDuringBattles", g_settings.noDeadEyeDuringBattles);
    g_settings.neverWantedDuringBattles = readIniBool("BattleModifiers", "NeverWantedDuringBattles", g_settings.neverWantedDuringBattles);
    g_settings.startCountdownSeconds = readIniClampedInt("BattleModifiers", "StartCountdownSeconds", g_settings.startCountdownSeconds, 0, 30);

    g_settings.bossExecutionHealthThreshold = readIniClampedInt("Protection", "BossExecutionHealthThreshold", g_settings.bossExecutionHealthThreshold, 0, 5000);
    g_settings.extremeExecutionHealthThreshold = readIniClampedInt("Protection", "ExtremeExecutionHealthThreshold", g_settings.extremeExecutionHealthThreshold, 0, 5000);
    g_settings.bossBlockedExecutionDamage = readIniClampedInt("Protection", "BlockedExecutionDamage", g_settings.bossBlockedExecutionDamage, 0, 1000);
    g_settings.bossDefensiveHealthThreshold = readIniClampedInt("BossCombat", "DefensiveHealthThreshold", g_settings.bossDefensiveHealthThreshold, 1, 5000);
    g_settings.bossDodgeDeadEyeSuppressMs = readIniClampedDword("BossCombat", "DodgeDeadEyeSuppressMs", g_settings.bossDodgeDeadEyeSuppressMs, kBossDodgeDeadEyeMinMs, kBossDodgeDeadEyeMaxMs);

    g_settings.bossHealGunDelayMs = readIniClampedDword("BossHealing", "GunDelayMs", g_settings.bossHealGunDelayMs, 0, 120000);
    g_settings.bossHealMeleeDelayMs = readIniClampedDword("BossHealing", "MeleeDelayMs", g_settings.bossHealMeleeDelayMs, 0, 120000);
    g_settings.bossHealGunTickMs = readIniClampedDword("BossHealing", "GunTickMs", g_settings.bossHealGunTickMs, 100, 120000);
    g_settings.bossHealMeleeTickMs = readIniClampedDword("BossHealing", "MeleeTickMs", g_settings.bossHealMeleeTickMs, 100, 120000);
    g_settings.bossHealAmount = readIniClampedInt("BossHealing", "HealAmount", g_settings.bossHealAmount, 0, 500);
    g_settings.regularHealDelayMs = readIniClampedDword("Healing", "RegularDelayMs", g_settings.regularHealDelayMs, 0, 120000);
    g_settings.regularHealTickMs = readIniClampedDword("Healing", "RegularTickMs", g_settings.regularHealTickMs, 100, 120000);
    g_settings.regularHealMinAmount = readIniClampedInt("Healing", "RegularMinAmount", g_settings.regularHealMinAmount, 0, 500);

    g_settings.immediateDeathmatchNpcCorpseCleanup = readIniBool("DeathmatchPerformance", "ImmediateNpcCorpseCleanup", g_settings.immediateDeathmatchNpcCorpseCleanup);
    g_settings.deathmatchCorpseVisibleMs = readIniClampedDword("DeathmatchPerformance", "CorpseVisibleMs", g_settings.deathmatchCorpseVisibleMs, 0, 5000);
    g_settings.deathmatchMaximumRespawnsPerFrame = readIniClampedInt("DeathmatchPerformance", "MaximumRespawnsPerFrame", g_settings.deathmatchMaximumRespawnsPerFrame, 1, 4);
    g_settings.deathmatchMinimumRespawnGapMs = readIniClampedDword("DeathmatchPerformance", "MinimumRespawnGapMs", g_settings.deathmatchMinimumRespawnGapMs, 0, 250);
    g_settings.deathmatchSnapshotRefreshMs = readIniClampedDword("DeathmatchPerformance", "SnapshotRefreshMs", g_settings.deathmatchSnapshotRefreshMs, 75, 1000);
    g_settings.deathmatchMaximumFullRetargetsPerFrame = readIniClampedInt("DeathmatchPerformance", "MaximumFullRetargetsPerFrame", g_settings.deathmatchMaximumFullRetargetsPerFrame, 2, 40);
    g_settings.largeDeathmatchThreshold = readIniClampedInt("DeathmatchPerformance", "LargeDeathmatchThreshold", g_settings.largeDeathmatchThreshold, 10, 300);
    g_settings.largeDeathmatchCombatUpdateMs = readIniClampedDword("DeathmatchPerformance", "LargeDeathmatchCombatUpdateMs", g_settings.largeDeathmatchCombatUpdateMs, 75, 500);
    g_settings.largeDeathmatchBlipValidationMs = readIniClampedDword("DeathmatchPerformance", "LargeDeathmatchBlipValidationMs", g_settings.largeDeathmatchBlipValidationMs, 900, 10000);
    g_settings.largeDeathmatchDynamicRepairMs = readIniClampedDword("DeathmatchPerformance", "LargeDeathmatchDynamicRepairMs", g_settings.largeDeathmatchDynamicRepairMs, 12000, 60000);
    g_settings.soloFfaIdleCheckMs = readIniClampedDword("DeathmatchPerformance", "SoloFfaIdleCheckMs", g_settings.soloFfaIdleCheckMs, 1200, 10000);
    g_settings.soloFfaIdleThresholdMs = readIniClampedDword("DeathmatchPerformance", "SoloFfaIdleThresholdMs", g_settings.soloFfaIdleThresholdMs, 2500, 30000);
    g_settings.preventPersistentDroppedWeapons = readIniBool("DeathmatchPerformance", "PreventPersistentDroppedWeapons", g_settings.preventPersistentDroppedWeapons);

    g_settings.enableIdleWatchdog = readIniBool("CombatRecovery", "EnableIdleWatchdog", g_settings.enableIdleWatchdog);
    g_settings.ordinaryIdleCheckIntervalMs = readIniClampedDword("CombatRecovery", "OrdinaryCheckIntervalMs", g_settings.ordinaryIdleCheckIntervalMs, 800, 10000);
    g_settings.ordinaryIdleThresholdMs = readIniClampedDword("CombatRecovery", "OrdinaryIdleThresholdMs", g_settings.ordinaryIdleThresholdMs, 1500, 30000);
    g_settings.ordinaryIdleConsecutiveChecks = readIniClampedInt("CombatRecovery", "OrdinaryConsecutiveChecks", g_settings.ordinaryIdleConsecutiveChecks, 1, 6);
    g_settings.idleSoftRecoveryDelayMs = readIniClampedDword("CombatRecovery", "SoftRecoveryDelayMs", g_settings.idleSoftRecoveryDelayMs, 300, 10000);
    g_settings.idleHardRecoveryCooldownMs = readIniClampedDword("CombatRecovery", "HardRecoveryCooldownMs", g_settings.idleHardRecoveryCooldownMs, 1000, 30000);
    g_settings.idleRepositionMinDistance = readIniClampedFloat("CombatRecovery", "RepositionMinDistance", g_settings.idleRepositionMinDistance, 1.0f, 20.0f);
    g_settings.idleRepositionMaxDistance = readIniClampedFloat("CombatRecovery", "RepositionMaxDistance", g_settings.idleRepositionMaxDistance, g_settings.idleRepositionMinDistance, 30.0f);
    g_settings.idleAllowForcedTargetChange = readIniBool("CombatRecovery", "AllowForcedTargetChange", g_settings.idleAllowForcedTargetChange);

    g_settings.minDeathmatchKillLimit = readIniClampedInt("Deathmatch", "MinKillLimit", g_settings.minDeathmatchKillLimit, 0, 5000);
    g_settings.maxDeathmatchKillLimit = readIniClampedInt("Deathmatch", "MaxKillLimit", g_settings.maxDeathmatchKillLimit, std::max(1, g_settings.minDeathmatchKillLimit), 5000);
    g_settings.defaultDeathmatchKillLimit = clampDeathmatchKillLimitValue(readIniInt("Deathmatch", "DefaultKillLimit", g_settings.defaultDeathmatchKillLimit));
    g_settings.npcDeathmatchRespawnDelayMs = readIniClampedDword("Deathmatch", "NpcRespawnDelayMs", g_settings.npcDeathmatchRespawnDelayMs, 250, 120000);
    g_settings.respawnTeamDeathmatchAtOriginalSpawn = readIniBool("Deathmatch", "RespawnTeamDeathmatchAtOriginalSpawn", g_settings.respawnTeamDeathmatchAtOriginalSpawn);

    g_settings.enableCorpseCleanup = readIniBool("Performance", "EnableCorpseCleanup", g_settings.enableCorpseCleanup);
    g_settings.normalCorpseLifetimeMs = readIniClampedDword("Performance", "NormalCorpseLifetimeMs", g_settings.normalCorpseLifetimeMs, 5000, 300000);
    g_settings.eliteCorpseLifetimeMs = readIniClampedDword("Performance", "EliteCorpseLifetimeMs", g_settings.eliteCorpseLifetimeMs, 5000, 300000);
    g_settings.maximumCorpseLifetimeMs = readIniClampedDword("Performance", "MaximumCorpseLifetimeMs", g_settings.maximumCorpseLifetimeMs, 15000, 600000);
    g_settings.corpseCleanupCheckMs = readIniClampedDword("Performance", "CorpseCleanupCheckMs", g_settings.corpseCleanupCheckMs, 500, 30000);
    g_settings.corpseCleanupMinPlayerDistance = readIniClampedFloat("Performance", "CorpseCleanupMinPlayerDistance", g_settings.corpseCleanupMinPlayerDistance, 10.0f, 150.0f);
    g_settings.preferredMaximumCorpses = readIniClampedInt("Performance", "PreferredMaximumCorpses", g_settings.preferredMaximumCorpses, 0, 500);
    g_settings.hardMaximumCorpses = readIniClampedInt("Performance", "HardMaximumCorpses", g_settings.hardMaximumCorpses, std::max(1, g_settings.preferredMaximumCorpses), 800);
    g_settings.cleanTrackedDroppedWeapons = readIniBool("Performance", "CleanTrackedDroppedWeapons", g_settings.cleanTrackedDroppedWeapons);
    g_settings.enableDistantBattleSimulation = readIniBool("Performance", "EnableDistantBattleSimulation", g_settings.enableDistantBattleSimulation);
    g_settings.distantBattleSimulationDistance = readIniClampedFloat("Performance", "DistantBattleSimulationDistance", g_settings.distantBattleSimulationDistance, 60.0f, 500.0f);
    g_settings.distantBattleSimulationDelayMs = readIniClampedDword("Performance", "DistantBattleSimulationDelayMs", g_settings.distantBattleSimulationDelayMs, 0, 60000);
    g_settings.distantBattleSimulationTickMs = readIniClampedDword("Performance", "DistantBattleSimulationTickMs", g_settings.distantBattleSimulationTickMs, 500, 60000);
    g_menu.killLimit = g_settings.defaultDeathmatchKillLimit;

    for (size_t i = 0; i < kDifficulty.size(); ++i)
        loadDifficultyTuning(kDifficultyIniSections[i], kDifficulty[i]);
    for (size_t i = 0; i < kBosses.size(); ++i)
        loadBossTuning(kBossIniSections[i], kBosses[i]);
    for (size_t i = 0; i < kSpecialPeds.size(); ++i)
        loadSpecialTuning(kSpecialIniSections[i], kSpecialPeds[i]);
}

bool exists(Entity entity)
{
    return entity != 0 && ENTITY::DOES_ENTITY_EXIST(entity);
}

void setPedActionMode(Ped ped, bool enabled)
{
    if (exists(ped))
        PED::SET_PED_USING_ACTION_MODE(ped, enabled, 0, const_cast<char*>("DEFAULT_ACTION"));
}

void setPedCrouchMovement(Ped ped, bool enabled)
{
    if (exists(ped))
        PED::SET_PED_STEALTH_MOVEMENT(ped, enabled, const_cast<char*>("DEFAULT_ACTION"), 0);
}

Vec3 fromNative(Vector3 value)
{
    return { value.x, value.y, value.z };
}

Vec3 entityCoords(Entity entity)
{
    return fromNative(ENTITY::GET_ENTITY_COORDS(entity, true, false));
}

float distanceSquared(Vec3 a, Vec3 b)
{
    float dx = a.x - b.x;
    float dy = a.y - b.y;
    float dz = a.z - b.z;
    return dx * dx + dy * dy + dz * dz;
}

Vec3 lerpVec3(Vec3 from, Vec3 to, float amount)
{
    amount = std::clamp(amount, 0.0f, 1.0f);
    return {
        from.x + (to.x - from.x) * amount,
        from.y + (to.y - from.y) * amount,
        from.z + (to.z - from.z) * amount
    };
}

Ped playerPed()
{
    return PLAYER::PLAYER_PED_ID();
}

int randomRange(int minValue, int maxValue)
{
    if (maxValue <= minValue)
        return minValue;
    return minValue + (std::rand() % (maxValue - minValue + 1));
}

float randomFloat(float minValue, float maxValue)
{
    if (maxValue <= minValue)
        return minValue;
    int steps = 1000;
    float t = static_cast<float>(randomRange(0, steps)) / static_cast<float>(steps);
    return minValue + (maxValue - minValue) * t;
}

void setStatus(const std::string& text, DWORD durationMs = 4500)
{
    g_runtime.status = text;
    g_runtime.lastStatusUntil = now() + durationMs;
}

void setBattleRespawnOverride(bool enabled)
{
    if (g_runtime.playerRespawnOverrideActive == enabled)
        return;

    GAMEPLAY::_DISABLE_AUTOMATIC_RESPAWN(enabled);
    GAMEPLAY::SET_FADE_IN_AFTER_DEATH_ARREST(!enabled);
    GAMEPLAY::SET_FADE_IN_AFTER_LOAD(!enabled);
    SCRIPT::SET_NO_LOADING_SCREEN(enabled);
    g_runtime.playerRespawnOverrideActive = enabled;
}

void suppressWantedDuringBattle()
{
    Player player = PLAYER::PLAYER_ID();
    if (!g_runtime.wantedSuppressionActive)
    {
        g_runtime.previousMaxWantedLevel = PLAYER::GET_MAX_WANTED_LEVEL();
        g_runtime.wantedSuppressionActive = true;
    }

    PLAYER::SET_MAX_WANTED_LEVEL(0);
    PLAYER::SET_WANTED_LEVEL_MULTIPLIER(0.0f);
    PLAYER::SET_PLAYER_WANTED_LEVEL(player, 0, true);
    PLAYER::CLEAR_PLAYER_WANTED_LEVEL(player);
    PURSUIT::SET_PLAYER_WANTED_INTENSITY(player, 0);
    PLAYER::CLEAR_PLAYER_HAS_DAMAGED_AT_LEAST_ONE_PED(player);
    PLAYER::CLEAR_PLAYER_HAS_DAMAGED_AT_LEAST_ONE_NON_ANIMAL_PED(player);
}

void restoreWantedAfterBattle()
{
    if (!g_runtime.wantedSuppressionActive)
        return;

    Player player = PLAYER::PLAYER_ID();
    PLAYER::CLEAR_PLAYER_WANTED_LEVEL(player);
    PURSUIT::SET_PLAYER_WANTED_INTENSITY(player, 0);
    PLAYER::SET_WANTED_LEVEL_MULTIPLIER(1.0f);
    PLAYER::SET_MAX_WANTED_LEVEL(std::max(0, g_runtime.previousMaxWantedLevel));
    PLAYER::RESET_WANTED_LEVEL_DIFFICULTY(player);
    g_runtime.wantedSuppressionActive = false;
}

void rememberPlayerSafePosition()
{
    Ped player = playerPed();
    if (!exists(player) ||
        PLAYER::IS_PLAYER_DEAD(PLAYER::PLAYER_ID()) ||
        PED::IS_PED_DEAD_OR_DYING(player, true) ||
        PED::IS_PED_FATALLY_INJURED(player))
    {
        return;
    }

    g_runtime.playerLastSafePos = entityCoords(player);
    g_runtime.playerLastSafeHeading = ENTITY::GET_ENTITY_HEADING(player);
    g_runtime.playerSafePosValid = true;
}

void rememberPlayerRevivePosition()
{
    Ped player = playerPed();
    if (!exists(player))
        return;

    g_runtime.playerLastSafePos = entityCoords(player);
    g_runtime.playerLastSafeHeading = ENTITY::GET_ENTITY_HEADING(player);
    g_runtime.playerSafePosValid = true;
}

bool requestModel(Hash model)
{
    if (!STREAMING::IS_MODEL_VALID(model) || !STREAMING::IS_MODEL_IN_CDIMAGE(model))
        return false;

    STREAMING::REQUEST_MODEL(model, false);
    int guard = 0;
    while (!STREAMING::HAS_MODEL_LOADED(model) && guard++ < 220)
        WAIT(0);
    return STREAMING::HAS_MODEL_LOADED(model);
}

Hash requestAnyModel(const std::array<const char*, 6>& models, int seed)
{
    for (size_t attempt = 0; attempt < models.size(); ++attempt)
    {
        const char* modelName = models[(static_cast<size_t>(seed) + attempt) % models.size()];
        if (!modelName || !*modelName)
            continue;

        Hash model = joaat(modelName);
        if (requestModel(model))
            return model;
    }
    return 0;
}

Hash requestAnyBossModel(const BossDef& boss, int seed)
{
    (void)seed;
    for (const char* modelName : boss.models)
    {
        if (!modelName || !*modelName)
            continue;

        Hash model = joaat(modelName);
        if (requestModel(model))
            return model;
    }
    return 0;
}

Hash requestAnyNamedPedModel(const NamedPedDef& ped)
{
    for (const char* modelName : ped.models)
    {
        if (!modelName || !*modelName)
            continue;

        Hash model = joaat(modelName);
        if (requestModel(model))
            return model;
    }
    return 0;
}

Hash requestAnySpecialPedModel(const SpecialPedDef& ped)
{
    for (const char* modelName : ped.models)
    {
        if (!modelName || !*modelName)
            continue;

        Hash model = joaat(modelName);
        if (requestModel(model))
            return model;
    }
    return 0;
}

bool namedCharacterAlreadySpawned(const char* name)
{
    if (!name || !*name)
        return false;

    for (const Fighter& fighter : g_runtime.fighters)
    {
        if (fighter.baseName == name)
            return true;
    }
    return false;
}

bool namedCharacterReservedByBossOrSpecial(const char* name)
{
    if (!name || !*name)
        return false;

    for (const TeamSetup& team : g_teams)
    {
        for (const TeamRosterSlot& slot : team.sets)
        {
            if (slot.count <= 0)
                continue;

            if (slot.difficulty == Difficulty::Bosses &&
                std::string(kBosses[static_cast<size_t>(slot.boss)].name) == name)
            {
                return true;
            }

            if (slot.difficulty == Difficulty::Special &&
                std::string(kSpecialPeds[static_cast<size_t>(slot.special)].name) == name)
            {
                return true;
            }
        }
    }

    return false;
}

Hash requestUniqueNamedPedModel(int pedSet, int seed, const NamedPedDef*& selectedPed)
{
    selectedPed = nullptr;
    size_t setSize = uniqueNamedPedSetSize(pedSet);
    for (size_t attempt = 0; attempt < setSize; ++attempt)
    {
        const NamedPedDef& ped = uniqueNamedPedForSet(pedSet, (static_cast<size_t>(seed) + attempt) % setSize);
        if (namedCharacterAlreadySpawned(ped.name) || namedCharacterReservedByBossOrSpecial(ped.name))
            continue;

        Hash model = requestAnyNamedPedModel(ped);
        if (!model)
            continue;

        selectedPed = &ped;
        return model;
    }
    return 0;
}

void snapToGround(Vec3& pos)
{
    float groundZ{};
    if (GAMEPLAY::GET_GROUND_Z_FOR_3D_COORD(pos.x, pos.y, pos.z + 70.0f, &groundZ, false))
        pos.z = groundZ;
}

bool spawnPointInWater(const Vec3& pos)
{
    float waterHeight{};
    if (!WATER::GET_WATER_HEIGHT(pos.x, pos.y, pos.z + 3.0f, &waterHeight))
        return false;

    return waterHeight > pos.z - kSpawnSafetyWaterMargin;
}

bool spawnPointInInterior(const Vec3& pos)
{
    return INTERIOR::GET_INTERIOR_AT_COORDS(pos.x, pos.y, pos.z) != 0;
}

bool spawnPointTooCloseToBattlePed(const Vec3& candidate, float minSpacing)
{
    if (minSpacing <= 0.0f)
        return false;

    float threshold = minSpacing * minSpacing;
    for (const Fighter& fighter : g_runtime.fighters)
    {
        if (!exists(fighter.ped) ||
            PED::IS_PED_DEAD_OR_DYING(fighter.ped, true) ||
            PED::IS_PED_FATALLY_INJURED(fighter.ped))
        {
            continue;
        }

        if (distanceSquared(candidate, entityCoords(fighter.ped)) < threshold)
            return true;
    }

    return false;
}

bool spawnPointAboveNearbyRoad(const Vec3& candidate)
{
    Vector3 node{};
    if (!PATHFIND::GET_NTH_CLOSEST_VEHICLE_NODE(candidate.x, candidate.y, candidate.z, 1, &node, true, 3.0f, 0.0f))
        return false;

    Vec3 road = fromNative(node);
    float dx = candidate.x - road.x;
    float dy = candidate.y - road.y;
    float horizontalSq = dx * dx + dy * dy;
    return horizontalSq <= kSpawnRoofRoadRejectRadius * kSpawnRoofRoadRejectRadius &&
        candidate.z - road.z > kSpawnRoofRoadRejectHeight;
}

bool safeSpawnCandidate(Vec3 requested, Vec3 candidate, bool strictHeight, float minSpacing)
{
    if (!std::isfinite(candidate.x) || !std::isfinite(candidate.y) || !std::isfinite(candidate.z))
        return false;

    if (spawnPointInWater(candidate) || spawnPointInInterior(candidate))
        return false;

    if (strictHeight && std::fabs(candidate.z - requested.z) > kSpawnSafetyMaxHeightDelta)
        return false;

    if (spawnPointAboveNearbyRoad(candidate))
        return false;

    if (spawnPointTooCloseToBattlePed(candidate, minSpacing))
        return false;

    return true;
}

bool tryPedSafeCoord(
    Vec3 requested,
    Vec3& out,
    float minSpacing,
    bool preferExact = false,
    bool allowUnloadedGround = false)
{
    STREAMING::REQUEST_COLLISION_AT_COORD(requested.x, requested.y, requested.z);
    PATHFIND::ADD_NAVMESH_REQUIRED_REGION(requested.x, requested.y, 12.0f);

    Vec3 grounded = requested;
    snapToGround(grounded);

    auto useGroundedIfValid = [&]() {
        bool navmeshLoaded = PATHFIND::IS_NAVMESH_LOADED_IN_AREA(
            grounded.x - 3.0f,
            grounded.y - 3.0f,
            grounded.z - 3.0f,
            grounded.x + 3.0f,
            grounded.y + 3.0f,
            grounded.z + 3.0f);
        if ((navmeshLoaded || allowUnloadedGround || preferExact) &&
            safeSpawnCandidate(requested, grounded, false, minSpacing))
        {
            out = grounded;
            return true;
        }

        return false;
    };

    if (preferExact && useGroundedIfValid())
        return true;

    Vector3 safe{};
    if (PATHFIND::GET_SAFE_COORD_FOR_PED(grounded.x, grounded.y, grounded.z, true, &safe, 0))
    {
        Vec3 candidate = fromNative(safe);
        snapToGround(candidate);
        if (safeSpawnCandidate(requested, candidate, true, minSpacing))
        {
            out = candidate;
            return true;
        }
    }

    if (!preferExact && useGroundedIfValid())
        return true;

    return false;
}

bool tryNearbyRoadNodeSpawn(
    Vec3 requested,
    int nth,
    int seed,
    Vec3& out,
    float minSpacing,
    bool allowUnloadedGround = false)
{
    Vector3 node{};
    if (!PATHFIND::GET_NTH_CLOSEST_VEHICLE_NODE(requested.x, requested.y, requested.z, nth, &node, true, 3.0f, 0.0f))
        return false;

    Vec3 nodePos = fromNative(node);
    for (int jitter = 0; jitter < 5; ++jitter)
    {
        Vec3 candidate = nodePos;
        if (jitter > 0)
        {
            float angle = static_cast<float>(((seed + nth * 53 + jitter * 89) % 360)) * (kPi / 180.0f);
            float radius = 0.85f + static_cast<float>(jitter - 1) * 1.05f;
            candidate.x += std::sin(angle) * radius;
            candidate.y += std::cos(angle) * radius;
        }

        if (tryPedSafeCoord(candidate, out, minSpacing, true, allowUnloadedGround))
            return true;
    }

    return false;
}

bool resolveSafeSpawnPoint(Vec3 requested, int seed, Vec3& out, bool preferRoadNodes)
{
    if (preferRoadNodes)
    {
        for (int attempt = 0; attempt < 24; ++attempt)
        {
            int nthNode = 1 + ((seed + attempt * 5) % 24);
            float minSpacing = attempt < 16 ? kSpawnStrictMinSpacing : kSpawnRelaxedMinSpacing;
            if (tryNearbyRoadNodeSpawn(requested, nthNode, seed + attempt * 97, out, minSpacing))
                return true;
        }
    }

    bool naturalLayout = !preferRoadNodes;
    if (tryPedSafeCoord(requested, out, kSpawnStrictMinSpacing, naturalLayout, naturalLayout) ||
        tryPedSafeCoord(requested, out, kSpawnRelaxedMinSpacing, naturalLayout, naturalLayout))
    {
        return true;
    }

    float angleBase = static_cast<float>((seed * 47) % 360) * (kPi / 180.0f);
    for (int attempt = 1; attempt <= kSpawnSafetySearchAttempts; ++attempt)
    {
        int ring = (attempt - 1) / 8;
        float radius = 2.0f + static_cast<float>(ring) * 3.8f;
        float angle = angleBase + static_cast<float>(attempt) * 2.39996323f;
        Vec3 candidate{
            requested.x + std::sin(angle) * radius,
            requested.y + std::cos(angle) * radius,
            requested.z
        };

        float minSpacing = attempt <= 64 ? kSpawnStrictMinSpacing : kSpawnRelaxedMinSpacing;
        if (preferRoadNodes && attempt % 2 == 0)
        {
            int nthNode = 1 + ((seed + attempt * 3) % 24);
            if (tryNearbyRoadNodeSpawn(candidate, nthNode, seed + attempt * 113, out, minSpacing))
                return true;
        }

        if (tryPedSafeCoord(candidate, out, minSpacing, naturalLayout, naturalLayout))
            return true;

        if (!preferRoadNodes && attempt % 8 == 0)
        {
            int nthNode = std::max(1, attempt / 8);
            if (tryNearbyRoadNodeSpawn(candidate, nthNode, seed + attempt * 113, out, minSpacing))
                return true;
        }
    }

    for (int nthNode = 1; nthNode <= 12; ++nthNode)
    {
        if (tryNearbyRoadNodeSpawn(requested, nthNode, seed + nthNode * 131, out, kSpawnRelaxedMinSpacing))
            return true;
    }

    if (preferRoadNodes)
    {
        for (int nthNode = 1; nthNode <= 72; ++nthNode)
        {
            if (tryNearbyRoadNodeSpawn(requested, nthNode, seed + nthNode * 211, out, kSpawnEmergencyMinSpacing, true))
                return true;
        }
    }

    for (int attempt = 1; attempt <= 48; ++attempt)
    {
        int ring = (attempt - 1) / 8;
        float radius = 6.0f + static_cast<float>(ring) * 6.0f;
        float angle = angleBase + static_cast<float>(attempt) * 2.39996323f;
        Vec3 candidate{
            requested.x + std::sin(angle) * radius,
            requested.y + std::cos(angle) * radius,
            requested.z
        };

        if (tryPedSafeCoord(candidate, out, kSpawnEmergencyMinSpacing, preferRoadNodes, true))
            return true;
    }

    return false;
}

float battleSpawnDistance()
{
    switch (g_menu.battleType)
    {
    case BattleType::AllWeapons:
        return g_settings.firearmSpawnDistance;
    case BattleType::MeleeOnly:
        return g_settings.meleeSpawnDistance;
    case BattleType::NoWeapons:
        return g_settings.unarmedSpawnDistance;
    }
    return g_settings.firearmSpawnDistance;
}

float defaultSpawnDistanceForType(BattleType type)
{
    switch (type)
    {
    case BattleType::AllWeapons:
        return 26.0f;
    case BattleType::MeleeOnly:
        return 12.0f;
    case BattleType::NoWeapons:
        return 8.0f;
    }
    return 26.0f;
}

float& editableSpawnDistance()
{
    switch (g_menu.battleType)
    {
    case BattleType::AllWeapons:
        return g_settings.firearmSpawnDistance;
    case BattleType::MeleeOnly:
        return g_settings.meleeSpawnDistance;
    case BattleType::NoWeapons:
        return g_settings.unarmedSpawnDistance;
    }
    return g_settings.firearmSpawnDistance;
}

void adjustSpawnDistance(int direction)
{
    float step = (GetAsyncKeyState(VK_SHIFT) & 0x8000) ? 5.0f : 1.0f;
    float& distance = editableSpawnDistance();
    distance = std::clamp(distance + static_cast<float>(direction) * step, 2.0f, kMaxBattleSpawnDistance);
}

float spawnDistanceScale()
{
    float base = defaultSpawnDistanceForType(g_menu.battleType);
    if (base <= 0.0f)
        return 1.0f;
    return std::clamp(battleSpawnDistance() / base, 0.15f, 8.0f);
}

std::string spawnDistanceText()
{
    char buffer[48]{};
    std::snprintf(buffer, sizeof(buffer), "%.0f", battleSpawnDistance());
    return buffer;
}

std::string floatSettingText(const char* label, float value)
{
    char buffer[96]{};
    std::snprintf(buffer, sizeof(buffer), "%s: %.0f", label, value);
    return buffer;
}

std::string distanceLimitSettingText(const char* label, float value)
{
    if (value <= 0.0f)
        return std::string(label) + ": Unlimited";

    return floatSettingText(label, value);
}

std::string intSettingText(const char* label, int value)
{
    char buffer[96]{};
    std::snprintf(buffer, sizeof(buffer), "%s: %d", label, value);
    return buffer;
}

std::string dwordSettingText(const char* label, DWORD value)
{
    char buffer[96]{};
    std::snprintf(buffer, sizeof(buffer), "%s: %lu ms", label, static_cast<unsigned long>(value));
    return buffer;
}

std::string toggleSettingText(const char* label, bool enabled)
{
    return std::string(label) + ": " + (enabled ? "On" : "Off");
}

std::string secondsSettingText(const char* label, int seconds)
{
    if (seconds <= 0)
        return std::string(label) + ": Off";

    char buffer[96]{};
    std::snprintf(buffer, sizeof(buffer), "%s: %ds", label, seconds);
    return buffer;
}

std::string killLimitText()
{
    if (!deathmatchMode(g_menu.mode))
        return "Off";

    int limit = clampDeathmatchKillLimitValue(g_menu.killLimit);
    if (limit <= 0)
        return "Endless";

    char buffer[32]{};
    std::snprintf(buffer, sizeof(buffer), "%d", limit);
    return buffer;
}

bool manualTeamSpawnActive(int team)
{
    return !g_runtime.freeForAll &&
        g_settings.enableManualTeamSpawns &&
        team >= 0 &&
        team < kTeamCount &&
        g_teams[static_cast<size_t>(team)].manualSpawnSet;
}

void teamRingColor(PlayerRelation relation, int& r, int& g, int& b)
{
    switch (relation)
    {
    case PlayerRelation::Friendly:
        r = 55;
        g = 215;
        b = 95;
        break;
    case PlayerRelation::Hostile:
        r = 225;
        g = 45;
        b = 38;
        break;
    case PlayerRelation::Neutral:
    default:
        r = 70;
        g = 155;
        b = 240;
        break;
    }
}

void drawMarkerType(Any type, Vec3 pos, float scaleX, float scaleY, float scaleZ, int r, int g, int b, int a)
{
    GRAPHICS::_0x2A32FAA57B937173(
        type,
        pos.x,
        pos.y,
        pos.z,
        0.0f,
        0.0f,
        0.0f,
        0.0f,
        0.0f,
        0.0f,
        scaleX,
        scaleY,
        scaleZ,
        r,
        g,
        b,
        a,
        false,
        false,
        2,
        false,
        nullptr,
        nullptr,
        false);
}

void drawSpawnRing(Vec3 pos, int r, int g, int b)
{
    STREAMING::REQUEST_COLLISION_AT_COORD(pos.x, pos.y, pos.z);
    GRAPHICS::DRAW_LIGHT_WITH_RANGE(pos.x, pos.y, pos.z + 0.28f, r, g, b, 3.0f, 1.20f);

    drawMarkerType(kRdr2MarkerCylinder, Vec3{ pos.x, pos.y, pos.z + 0.004f }, 4.6f, 4.6f, 0.035f, r, g, b, 205);
    drawMarkerType(kRdr2MarkerCylinder, Vec3{ pos.x, pos.y, pos.z + 0.018f }, 0.50f, 0.50f, 0.08f, 245, 236, 218, 210);

    constexpr int kRingPoints = 28;
    constexpr float kRingRadius = 3.2f;
    for (int i = 0; i < kRingPoints; ++i)
    {
        float angle = (static_cast<float>(i) / static_cast<float>(kRingPoints)) * kPi * 2.0f;
        Vec3 point{
            pos.x + std::sin(angle) * kRingRadius,
            pos.y + std::cos(angle) * kRingRadius,
            pos.z + 0.008f
        };
        drawMarkerType(kRdr2MarkerCylinder, point, 0.28f, 0.28f, 0.13f, r, g, b, 235);
    }
}

void drawManualTeamSpawnMarkers()
{
    if (!g_settings.enableManualTeamSpawns ||
        freeForAllSelected() ||
        g_runtime.battleActive ||
        battlePreparationActive())
    {
        return;
    }

    for (int team = 0; team < kTeamCount; ++team)
    {
        const TeamSetup& setup = g_teams[static_cast<size_t>(team)];
        if (!setup.manualSpawnSet)
            continue;

        int r = 255;
        int g = 255;
        int b = 255;
        teamRingColor(setup.playerRelation, r, g, b);
        drawSpawnRing(setup.manualSpawn, r, g, b);
    }
}

Vec3 teamCenter(int team)
{
    if (manualTeamSpawnActive(team))
    {
        return g_teams[static_cast<size_t>(team)].manualSpawn;
    }

    Vec3 player = entityCoords(playerPed());
    float heading = (ENTITY::GET_ENTITY_HEADING(playerPed()) * (kPi / 180.0f)) + kPi;
    float distance = battleSpawnDistance();
    float defaultDistance = defaultSpawnDistanceForType(g_menu.battleType);
    float playerGap = std::max(10.0f, defaultDistance * 0.65f);
    float midLine = playerGap + (distance * 0.5f);
    float lateral = std::max(6.0f, distance * 0.75f);

    float forwardOffset = playerGap;
    float sideOffset = 0.0f;
    switch (team)
    {
    case 0:
        forwardOffset = playerGap;
        break;
    case 1:
        forwardOffset = playerGap + distance;
        break;
    case 2:
        forwardOffset = midLine;
        sideOffset = lateral;
        break;
    case 3:
        forwardOffset = midLine;
        sideOffset = -lateral;
        break;
    default:
        break;
    }

    float side = heading + (kPi * 0.5f);
    Vec3 pos{
        player.x + std::sin(heading) * forwardOffset + std::sin(side) * sideOffset,
        player.y + std::cos(heading) * forwardOffset + std::cos(side) * sideOffset,
        player.z
    };
    snapToGround(pos);
    return pos;
}

Vec3 freeForAllScatterOffset(int index)
{
    if (index <= 0)
        return Vec3{};

    int scatterIndex = index - 1;
    float scale = spawnDistanceScale();
    float baseRadius = (g_menu.battleType == BattleType::AllWeapons ? 8.0f : 3.2f) * scale;
    float ringStep = (g_menu.battleType == BattleType::AllWeapons ? 4.8f : 2.8f) * scale;
    int ring = scatterIndex / 10;
    float angle = g_runtime.freeForAllSpawnAngle + static_cast<float>(scatterIndex) * 2.39996323f;
    float jitter = static_cast<float>((scatterIndex * 37) % 100) * 0.018f * scale;
    float radius = baseRadius + static_cast<float>(ring) * ringStep + jitter;

    return Vec3{
        std::sin(angle) * radius,
        std::cos(angle) * radius,
        0.0f
    };
}

float formationForwardForTeam(int team)
{
    if (manualTeamSpawnActive(team))
    {
        Vec3 spawn = g_teams[static_cast<size_t>(team)].manualSpawn;
        Vec3 center = g_runtime.battleCenter;
        if (!std::isfinite(center.x) || !std::isfinite(center.y) || !std::isfinite(center.z))
            center = entityCoords(playerPed());

        if (distanceSquared(spawn, center) > 1.0f)
            return GAMEPLAY::GET_HEADING_FROM_VECTOR_2D(center.x - spawn.x, center.y - spawn.y) * (kPi / 180.0f);
    }

    float heading = (ENTITY::GET_ENTITY_HEADING(playerPed()) * (kPi / 180.0f)) + kPi;
    switch (team)
    {
    case 0:
        return heading;
    case 1:
        return heading + kPi;
    case 2:
        return heading - (kPi * 0.5f);
    case 3:
        return heading + (kPi * 0.5f);
    default:
        return heading;
    }
}

Vec3 spawnSlot(int team, int index)
{
    if (g_runtime.freeForAll)
    {
        Vec3 player = entityCoords(playerPed());
        int virtualIndex = g_runtime.playerParticipating ? index : index + 1;
        Vec3 center = player;
        if (g_runtime.playerParticipating && g_runtime.freeForAllPlayerScatterIndex >= 0)
        {
            if (virtualIndex >= g_runtime.freeForAllPlayerScatterIndex)
                ++virtualIndex;
            Vec3 playerOffset = freeForAllScatterOffset(g_runtime.freeForAllPlayerScatterIndex);
            center.x -= playerOffset.x;
            center.y -= playerOffset.y;
        }

        Vec3 offset = freeForAllScatterOffset(virtualIndex);
        Vec3 pos{
            center.x + offset.x,
            center.y + offset.y,
            center.z
        };
        snapToGround(pos);
        return pos;
    }

    Vec3 center = teamCenter(team);
    float forward = formationForwardForTeam(team);
    float side = forward + (kPi * 0.5f);

    int row = index / 5;
    int col = index % 5;
    float sideOffset = (static_cast<float>(col) - 2.0f) * 2.25f;
    float backOffset = static_cast<float>(row) * -2.35f;

    Vec3 pos{
        center.x + std::sin(side) * sideOffset + std::sin(forward) * backOffset,
        center.y + std::cos(side) * sideOffset + std::cos(forward) * backOffset,
        center.z
    };
    if (!manualTeamSpawnActive(team))
        snapToGround(pos);
    return pos;
}

bool resolveManualSpawnPoint(Vec3 requested, int seed, int attempt, Vec3& out)
{
    if (!std::isfinite(requested.x) || !std::isfinite(requested.y) || !std::isfinite(requested.z))
        return false;

    Vec3 candidate = requested;
    if (attempt > 0)
    {
        float angle = static_cast<float>(((seed + 1) * 41 + attempt * 79) % 360) * (kPi / 180.0f);
        float radius = 1.0f + static_cast<float>((attempt - 1) % 5) * 1.15f + static_cast<float>((attempt - 1) / 5) * 1.35f;
        candidate.x += std::sin(angle) * radius;
        candidate.y += std::cos(angle) * radius;
    }

    STREAMING::REQUEST_COLLISION_AT_COORD(candidate.x, candidate.y, candidate.z);
    PATHFIND::ADD_NAVMESH_REQUIRED_REGION(candidate.x, candidate.y, 8.0f);

    float groundZ{};
    if (GAMEPLAY::GET_GROUND_Z_FOR_3D_COORD(candidate.x, candidate.y, candidate.z + 2.0f, &groundZ, false) &&
        std::fabs(groundZ - candidate.z) <= 2.5f)
    {
        candidate.z = groundZ;
    }

    float minSpacing = attempt < 18 ? kSpawnRelaxedMinSpacing : kSpawnEmergencyMinSpacing;
    if (spawnPointTooCloseToBattlePed(candidate, minSpacing))
        return false;

    out = candidate;
    return true;
}

bool resolveSpawnSlotPosition(int team, int index, int attempt, Vec3& out)
{
    Vec3 base = spawnSlot(team, index);
    Vec3 requested = base;
    bool manualSpawn = manualTeamSpawnActive(team);
    if (manualSpawn)
        return resolveManualSpawnPoint(requested, index + attempt * 29 + team * 101, attempt, out);

    if (attempt > 0)
    {
        Vec3 center = g_runtime.battleCenter;
        if (!std::isfinite(center.x) || !std::isfinite(center.y) || !std::isfinite(center.z))
            center = entityCoords(playerPed());

        bool farSlot =
            (battleSpawnDistance() >= kSpawnInwardFallbackDistance ||
             distanceSquared(base, center) >= kSpawnInwardFallbackDistance * kSpawnInwardFallbackDistance);
        if (farSlot && attempt >= kSpawnInwardFallbackAttempt)
        {
            int phase = attempt - kSpawnInwardFallbackAttempt;
            constexpr std::array<float, 7> inwardScales{ 0.86f, 0.72f, 0.58f, 0.44f, 0.30f, 0.18f, 0.10f };
            float keepScale = inwardScales[std::min(static_cast<size_t>(phase / 4), inwardScales.size() - 1)];
            requested.x = center.x + (base.x - center.x) * keepScale;
            requested.y = center.y + (base.y - center.y) * keepScale;
            requested.z = base.z;

            float angle = static_cast<float>(((index + 1) * 53 + attempt * 97 + team * 31) % 360) * (kPi / 180.0f);
            float radius = 3.0f + static_cast<float>(phase % 4) * 4.0f + static_cast<float>(phase / 16) * 5.0f;
            requested.x += std::sin(angle) * radius;
            requested.y += std::cos(angle) * radius;
        }
        else
        {
            float angle = static_cast<float>(((index + 1) * 37 + attempt * 71) % 360) * (kPi / 180.0f);
            float radius = 2.0f + static_cast<float>((attempt - 1) % 4) * 2.5f + static_cast<float>((attempt - 1) / 4) * 3.0f;
            requested.x += std::sin(angle) * radius;
            requested.y += std::cos(angle) * radius;
        }
    }

    bool preferRoadNodes = false;
    return resolveSafeSpawnPoint(requested, index + attempt * 29 + team * 101, out, preferRoadNodes);
}

float headingToward(Vec3 from, Vec3 to)
{
    return GAMEPLAY::GET_HEADING_FROM_VECTOR_2D(to.x - from.x, to.y - from.y);
}

bool isTeamRelationshipGroup(Hash group);
bool isFreeForAllRelationshipGroup(Hash group);

bool tryCreateRelationshipGroup(const char* name, Hash& outGroup, bool unique)
{
    outGroup = 0;
    if (!name || !*name)
        return false;

    Hash group{};
    PED::ADD_RELATIONSHIP_GROUP(const_cast<char*>(name), &group);
    if (!group)
        return false;

    if (unique && (isTeamRelationshipGroup(group) || isFreeForAllRelationshipGroup(group)))
        return false;

    outGroup = group;
    return true;
}

bool createRelationshipGroups()
{
    const char* names[kTeamCount] = { "REL_BATTLE_TEAM_1", "REL_BATTLE_TEAM_2", "REL_BATTLE_TEAM_3", "REL_BATTLE_TEAM_4" };
    for (int i = 0; i < kTeamCount; ++i)
    {
        if (g_runtime.groups[i])
            continue;

        Hash group{};
        if (!tryCreateRelationshipGroup(names[i], group, false))
        {
            setStatus("Engine relationship-group limit reached", 7000);
            return false;
        }
        g_runtime.groups[i] = group;
        markRelationshipsDirty();
    }
    return true;
}

void markRelationshipsDirty()
{
    g_runtime.relationshipsDirty = true;
}

void rememberFreeForAllRelationshipGroup(Hash group)
{
    if (!group)
        return;

    if (std::find(g_runtime.freeForAllGroups.begin(), g_runtime.freeForAllGroups.end(), group) == g_runtime.freeForAllGroups.end())
        g_runtime.freeForAllGroups.push_back(group);
}

bool isTeamRelationshipGroup(Hash group)
{
    for (Hash teamGroup : g_runtime.groups)
    {
        if (teamGroup && teamGroup == group)
            return true;
    }
    return false;
}

bool isFreeForAllRelationshipGroup(Hash group)
{
    for (Hash ffaGroup : g_runtime.freeForAllGroups)
    {
        if (ffaGroup && ffaGroup == group)
            return true;
    }
    return false;
}

Hash createFreeForAllRelationshipGroup(int seed)
{
    char name[32]{};
    std::snprintf(name, sizeof(name), "REL_BATTLE_FFA_%05d", seed % 100000);
    Hash group{};
    if (!tryCreateRelationshipGroup(name, group, true))
    {
        setStatus("Engine relationship-group limit reached", 7000);
        return 0;
    }
    Hash resolved = group;
    rememberFreeForAllRelationshipGroup(resolved);
    markRelationshipsDirty();
    return resolved;
}

bool groupStillInUse(Hash group)
{
    if (!group)
        return false;

    if (g_runtime.playerFreeForAllGroup == group)
        return true;

    for (const Fighter& fighter : g_runtime.fighters)
    {
        if (fighter.group == group)
            return true;
    }

    return false;
}

void removeFreeForAllRelationshipGroup(Hash group)
{
    if (!group || groupStillInUse(group))
        return;

    PED::REMOVE_RELATIONSHIP_GROUP(group);
    g_runtime.freeForAllGroups.erase(
        std::remove(g_runtime.freeForAllGroups.begin(), g_runtime.freeForAllGroups.end(), group),
        g_runtime.freeForAllGroups.end());
    if (g_runtime.freeForAllSpawnGroup == group)
        g_runtime.freeForAllSpawnGroup = 0;
    markRelationshipsDirty();
}

void addUniqueGroup(std::vector<Hash>& groups, Hash group)
{
    if (group && std::find(groups.begin(), groups.end(), group) == groups.end())
        groups.push_back(group);
}

std::vector<Hash> activeFreeForAllGroups()
{
    std::vector<Hash> groups;
    groups.reserve(g_runtime.fighters.size() + 1);
    addUniqueGroup(groups, g_runtime.playerFreeForAllGroup);
    for (const Fighter& fighter : g_runtime.fighters)
        addUniqueGroup(groups, fighter.group);
    return groups;
}

std::vector<Hash> activeBattleGroups()
{
    if (g_runtime.freeForAll)
        return activeFreeForAllGroups();

    std::vector<Hash> groups;
    groups.reserve(kTeamCount);
    for (Hash group : g_runtime.groups)
        addUniqueGroup(groups, group);
    return groups;
}

void debugFreeForAllGroupCounts()
{
#if 0
    if (!g_runtime.freeForAll)
        return;

    int combatants = static_cast<int>(g_runtime.fighters.size()) + (g_runtime.playerParticipating ? 1 : 0);
    int teamSize = std::max(1, g_runtime.freeForAllTeamSize);
    int expected = (combatants + teamSize - 1) / teamSize;
    int actual = static_cast<int>(activeFreeForAllGroups().size());
    char buffer[160]{};
    std::snprintf(
        buffer,
        sizeof(buffer),
        "[BattleCreatorGroups] expected=%d actual=%d stored=%d temp=0x%08X fighters=%d\n",
        expected,
        actual,
        static_cast<int>(g_runtime.freeForAllGroups.size()),
        static_cast<unsigned int>(g_runtime.freeForAllSpawnGroup),
        static_cast<int>(g_runtime.fighters.size()));
    OutputDebugStringA(buffer);
#endif
}

int relationToPlayerValue(PlayerRelation relation)
{
    switch (relation)
    {
    case PlayerRelation::Friendly:
        return 0;
    case PlayerRelation::Neutral:
        return 3;
    case PlayerRelation::Hostile:
        return 5;
    }
    return 3;
}

bool freeForAllActive()
{
    return g_runtime.battleActive && g_runtime.freeForAll;
}

bool freeForAllSelected()
{
    return freeForAllMode(g_menu.mode);
}

bool deathmatchSelected()
{
    return deathmatchMode(g_menu.mode);
}

bool showKillLimitRow()
{
    return deathmatchSelected();
}

bool showManualTeamSpawnRows()
{
    return !freeForAllSelected() && g_settings.enableManualTeamSpawns;
}

bool menuLogicalRowVisible(int logicalRow)
{
    if (logicalRow == 3 && !showKillLimitRow())
        return false;

    if (!freeForAllSelected() &&
        (logicalRow == 5 || logicalRow == 6) &&
        !showManualTeamSpawnRows())
    {
        return false;
    }

    return true;
}

int maxLogicalMenuRows()
{
    return freeForAllSelected() ? kBattleRoyaleMenuRows : kTeamMenuRows;
}

int logicalMenuRow(int visibleRow)
{
    int visible = -1;
    int maxRows = maxLogicalMenuRows();
    for (int logical = 0; logical < maxRows; ++logical)
    {
        if (!menuLogicalRowVisible(logical))
            continue;

        ++visible;
        if (visible == visibleRow)
            return logical;
    }

    return std::clamp(visibleRow, 0, std::max(0, maxRows - 1));
}

int visibleMenuRow(int logicalRow)
{
    int visible = -1;
    int maxRows = maxLogicalMenuRows();
    for (int logical = 0; logical < maxRows && logical <= logicalRow; ++logical)
    {
        if (menuLogicalRowVisible(logical))
            ++visible;
    }

    return std::max(0, visible);
}

bool deathmatchActive()
{
    return g_runtime.battleActive && g_runtime.deathmatch;
}

bool deathmatchFinished()
{
    return g_runtime.deathmatch && g_runtime.resultAnnounced && !g_runtime.battleActive;
}

bool battlePreparationActive()
{
    return g_runtime.preparationPhase != BattlePreparationPhase::None &&
        g_runtime.preparationPhase != BattlePreparationPhase::Failed;
}

PlayerRelation runtimeRelationToPlayer(int team)
{
    if (deathmatchFinished())
        return PlayerRelation::Neutral;

    if (g_runtime.playerSpectating)
        return PlayerRelation::Neutral;

    if (g_runtime.freeForAll)
    {
        if (g_runtime.freeForAllSpectate || (g_runtime.playerEliminated && !g_runtime.deathmatch))
            return PlayerRelation::Neutral;
        return PlayerRelation::Hostile;
    }

    if (g_runtime.playerEliminated && !g_runtime.deathmatch)
        return PlayerRelation::Neutral;
    if (g_settings.neutralsFriendlyUntilAttacked &&
        team >= 0 &&
        team < kTeamCount &&
        g_teams[static_cast<size_t>(team)].playerRelation == PlayerRelation::Neutral &&
        g_runtime.neutralTeamProvokedByPlayer[static_cast<size_t>(team)])
    {
        return PlayerRelation::Hostile;
    }

    return g_teams[static_cast<size_t>(team)].playerRelation;
}

bool provokeNeutralTeamByPlayer(Fighter& fighter, DWORD t)
{
    if (!g_settings.neutralsFriendlyUntilAttacked ||
        g_runtime.freeForAll ||
        fighter.team < 0 ||
        fighter.team >= kTeamCount ||
        g_teams[static_cast<size_t>(fighter.team)].playerRelation != PlayerRelation::Neutral ||
        g_runtime.neutralTeamProvokedByPlayer[static_cast<size_t>(fighter.team)])
    {
        return false;
    }

    g_runtime.neutralTeamProvokedByPlayer[static_cast<size_t>(fighter.team)] = true;
    fighter.lastPlayerDamage = t;
    markRelationshipsDirty();
    updateRelationshipsIfNeeded(t);
    Ped player = playerPed();
    bool canAttackPlayer =
        g_runtime.battleActive &&
        !g_runtime.startCountdownActive &&
        !g_runtime.playerSpectating &&
        !(g_runtime.playerEliminated && !g_runtime.deathmatch) &&
        exists(player) &&
        !PED::IS_PED_DEAD_OR_DYING(player, true) &&
        !PED::IS_PED_FATALLY_INJURED(player);

    for (Fighter& teammate : g_runtime.fighters)
    {
        if (teammate.team == fighter.team)
        {
            removeFighterBlip(teammate);
            if (canAttackPlayer && isAlive(teammate))
            {
                PED::REGISTER_TARGET(teammate.ped, player, true);
                AI::TASK_COMBAT_PED(teammate.ped, player, 0, 16);
                teammate.currentTarget = player;
                teammate.lastTask = t;
                teammate.lastCombatActivityAt = t;
            }
        }
    }
    setStatus("Team " + std::to_string(fighter.team + 1) + " is hostile", 4500);
    return true;
}

PlayerRelation fighterRelationToPlayer(const Fighter& fighter)
{
    if (deathmatchFinished())
        return PlayerRelation::Neutral;

    if (g_runtime.playerSpectating)
        return PlayerRelation::Neutral;

    if (!g_runtime.freeForAll)
        return runtimeRelationToPlayer(fighter.team);

    if (g_runtime.freeForAllSpectate || (g_runtime.playerEliminated && !g_runtime.deathmatch))
        return PlayerRelation::Neutral;

    if (g_runtime.playerFreeForAllGroup && fighter.group == g_runtime.playerFreeForAllGroup)
        return PlayerRelation::Friendly;

    return PlayerRelation::Hostile;
}

int playerTeamForCurrentBattle()
{
    if (freeForAllSelected())
        return -1;

    for (int i = 0; i < kTeamCount; ++i)
    {
        if (g_teams[static_cast<size_t>(i)].playerRelation == PlayerRelation::Friendly &&
            teamEnabled(g_teams[static_cast<size_t>(i)]))
        {
            return i;
        }
    }
    return -1;
}

bool playerAliveInBattle()
{
    Ped player = playerPed();
    return g_runtime.playerParticipating &&
        !g_runtime.playerEliminated &&
        exists(player) &&
        !PED::IS_PED_DEAD_OR_DYING(player, true) &&
        !PED::IS_PED_FATALLY_INJURED(player);
}

int startCountdownRemainingSeconds()
{
    if (!g_runtime.startCountdownActive)
        return 0;

    DWORD t = now();
    if (t >= g_runtime.startCountdownEndsAt)
        return 0;

    DWORD remainingMs = g_runtime.startCountdownEndsAt - t;
    return static_cast<int>((remainingMs + 999u) / 1000u);
}

void applyRelationships()
{
    if (!g_runtime.freeForAll && !createRelationshipGroups())
        return;

    Hash playerGroup = PED::GET_PED_RELATIONSHIP_GROUP_HASH(playerPed());
    std::vector<Hash> groups = activeBattleGroups();
    if (g_runtime.startCountdownActive)
    {
        for (Hash group : groups)
        {
            PED::SET_RELATIONSHIP_BETWEEN_GROUPS(3, group, playerGroup);
            PED::SET_RELATIONSHIP_BETWEEN_GROUPS(3, playerGroup, group);
            PED::SET_RELATIONSHIP_BETWEEN_GROUPS(0, group, group);
        }
        for (size_t a = 0; a < groups.size(); ++a)
        {
            for (size_t b = a + 1; b < groups.size(); ++b)
            {
                PED::SET_RELATIONSHIP_BETWEEN_GROUPS(3, groups[a], groups[b]);
                PED::SET_RELATIONSHIP_BETWEEN_GROUPS(3, groups[b], groups[a]);
            }
        }
        g_runtime.relationshipsDirty = false;
        g_runtime.lastRelationshipSafetyRefresh = now();
        return;
    }

    if (deathmatchFinished())
    {
        for (Hash group : groups)
        {
            PED::SET_RELATIONSHIP_BETWEEN_GROUPS(3, group, playerGroup);
            PED::SET_RELATIONSHIP_BETWEEN_GROUPS(3, playerGroup, group);
            PED::SET_RELATIONSHIP_BETWEEN_GROUPS(0, group, group);
        }
        for (size_t a = 0; a < groups.size(); ++a)
        {
            for (size_t b = a + 1; b < groups.size(); ++b)
            {
                PED::SET_RELATIONSHIP_BETWEEN_GROUPS(3, groups[a], groups[b]);
                PED::SET_RELATIONSHIP_BETWEEN_GROUPS(3, groups[b], groups[a]);
            }
        }
        g_runtime.relationshipsDirty = false;
        g_runtime.lastRelationshipSafetyRefresh = now();
        return;
    }

    if (g_runtime.freeForAll)
    {
        for (Hash group : groups)
        {
            PlayerRelation relation = PlayerRelation::Hostile;
            if (g_runtime.freeForAllSpectate || g_runtime.playerSpectating || (g_runtime.playerEliminated && !g_runtime.deathmatch))
                relation = PlayerRelation::Neutral;
            else if (g_runtime.playerFreeForAllGroup && group == g_runtime.playerFreeForAllGroup)
                relation = PlayerRelation::Friendly;

            int playerRelation = relationToPlayerValue(relation);
            PED::SET_RELATIONSHIP_BETWEEN_GROUPS(playerRelation, group, playerGroup);
            PED::SET_RELATIONSHIP_BETWEEN_GROUPS(playerRelation, playerGroup, group);
            PED::SET_RELATIONSHIP_BETWEEN_GROUPS(0, group, group);
        }

        for (size_t a = 0; a < groups.size(); ++a)
        {
            for (size_t b = a + 1; b < groups.size(); ++b)
            {
                PED::SET_RELATIONSHIP_BETWEEN_GROUPS(5, groups[a], groups[b]);
                PED::SET_RELATIONSHIP_BETWEEN_GROUPS(5, groups[b], groups[a]);
            }
        }
        g_runtime.relationshipsDirty = false;
        g_runtime.lastRelationshipSafetyRefresh = now();
        return;
    }

    for (int i = 0; i < kTeamCount; ++i)
    {
        int relation = relationToPlayerValue(runtimeRelationToPlayer(i));
        PED::SET_RELATIONSHIP_BETWEEN_GROUPS(relation, g_runtime.groups[i], playerGroup);
        PED::SET_RELATIONSHIP_BETWEEN_GROUPS(relation, playerGroup, g_runtime.groups[i]);
        PED::SET_RELATIONSHIP_BETWEEN_GROUPS(0, g_runtime.groups[i], g_runtime.groups[i]);
    }

    for (int a = 0; a < kTeamCount; ++a)
    {
        for (int b = 0; b < kTeamCount; ++b)
        {
            if (a == b)
                continue;
            PED::SET_RELATIONSHIP_BETWEEN_GROUPS(5, g_runtime.groups[a], g_runtime.groups[b]);
        }
    }
    g_runtime.relationshipsDirty = false;
    g_runtime.lastRelationshipSafetyRefresh = now();
}

void updateRelationshipsIfNeeded(DWORD t)
{
    if (!g_runtime.relationshipsDirty)
        return;

    applyRelationships();
}

Hash fighterGroupForPed(Ped ped)
{
    for (const Fighter& fighter : g_runtime.fighters)
    {
        if (fighter.ped == ped)
            return fighter.group;
    }
    return 0;
}

const Fighter* fighterForPed(Ped ped)
{
    for (const Fighter& fighter : g_runtime.fighters)
    {
        if (fighter.ped == ped)
            return &fighter;
    }
    return nullptr;
}

bool isEliteBattlePed(Ped ped)
{
    const Fighter* fighter = fighterForPed(ped);
    return fighter &&
        (fighter->difficulty == Difficulty::Bosses ||
         fighter->difficulty == Difficulty::Special ||
         fighter->difficulty == Difficulty::Extreme);
}

bool eliteNpcDuelTarget(const Fighter& fighter, Ped target)
{
    return target != playerPed() &&
        (fighter.difficulty == Difficulty::Bosses || fighter.difficulty == Difficulty::Special) &&
        isEliteBattlePed(target);
}

void setDamagePermission(Ped ped, Hash group, bool canDamage)
{
    if (!exists(ped) || !group)
        return;

    ENTITY::SET_ENTITY_CAN_BE_DAMAGED_BY_RELATIONSHIP_GROUP(ped, canDamage, static_cast<int>(group));
}

void resetDamagePermissionCache(Fighter& fighter)
{
    fighter.damageBlockedGroup = 0;
    fighter.damageBlockedGroupValid = false;
    fighter.damagePlayerGroup = 0;
    fighter.damagePlayerAllowed = true;
    fighter.damagePlayerPermissionValid = false;
}

void applyDamagePermissions(Fighter& fighter)
{
    if (!exists(fighter.ped))
        return;

    Hash ownGroup = fighter.group ? fighter.group : fighterGroupForPed(fighter.ped);
    if (fighter.damageBlockedGroupValid && fighter.damageBlockedGroup != ownGroup)
    {
        setDamagePermission(fighter.ped, fighter.damageBlockedGroup, true);
        fighter.damageBlockedGroupValid = false;
        fighter.damageBlockedGroup = 0;
    }

    if (ownGroup && (!fighter.damageBlockedGroupValid || fighter.damageBlockedGroup != ownGroup))
    {
        setDamagePermission(fighter.ped, ownGroup, false);
        fighter.damageBlockedGroup = ownGroup;
        fighter.damageBlockedGroupValid = true;
    }

    Hash playerGroup = PED::GET_PED_RELATIONSHIP_GROUP_HASH(playerPed());
    bool canPlayerDamage = fighterRelationToPlayer(fighter) != PlayerRelation::Friendly;
    if (playerGroup &&
        (!fighter.damagePlayerPermissionValid ||
         fighter.damagePlayerGroup != playerGroup ||
         fighter.damagePlayerAllowed != canPlayerDamage))
    {
        setDamagePermission(fighter.ped, playerGroup, canPlayerDamage);
        fighter.damagePlayerGroup = playerGroup;
        fighter.damagePlayerAllowed = canPlayerDamage;
        fighter.damagePlayerPermissionValid = true;
    }
}

void validateRelationshipGroupAssignments(DWORD t)
{
    if (g_runtime.lastRelationshipValidation != 0 &&
        t - g_runtime.lastRelationshipValidation < kRelationshipValidationMs)
    {
        return;
    }

    g_runtime.lastRelationshipValidation = t;
    for (Fighter& fighter : g_runtime.fighters)
    {
        if (!exists(fighter.ped) || !fighter.group)
            continue;

        if (PED::GET_PED_RELATIONSHIP_GROUP_HASH(fighter.ped) == fighter.group)
            continue;

        PED::SET_PED_RELATIONSHIP_GROUP_DEFAULT_HASH(fighter.ped, fighter.group);
        PED::SET_PED_RELATIONSHIP_GROUP_HASH(fighter.ped, fighter.group);
        applyDamagePermissions(fighter);
        removeFighterBlip(fighter);
    }
}

bool isAlive(const Fighter& fighter);

Blip addBlipForEntity(Hash blipStyle, Entity entity)
{
    return invoke<Blip>(0x23F74C2FDA6E7C61, blipStyle, entity);
}

bool addBlipModifier(Blip blip, const char* modifier)
{
    if (!RADAR::DOES_BLIP_EXIST(blip) || !modifier || !*modifier)
        return false;
    return RADAR::_0x662D364ABF16DE2F(blip, joaat(modifier)) != 0;
}

bool addFirstBlipModifier(Blip blip, const char* const* modifiers, int count)
{
    for (int i = 0; i < count; ++i)
    {
        if (addBlipModifier(blip, modifiers[i]))
            return true;
    }
    return false;
}

void removeBlipModifier(Blip blip, const char* modifier)
{
    if (!RADAR::DOES_BLIP_EXIST(blip) || !modifier || !*modifier)
        return;
    RADAR::_0xB059D7BD3D78C16F(blip, joaat(modifier));
}

Hash fallbackBlipStyleForTeam(int team)
{
    PlayerRelation relation = runtimeRelationToPlayer(team);
    if (relation == PlayerRelation::Friendly || relation == PlayerRelation::Neutral)
        return joaat("BLIP_STYLE_COMPANION");
    if (relation == PlayerRelation::Hostile)
        return joaat("BLIP_STYLE_ENEMY");
    return joaat("BLIP_STYLE_COMPANION");
}

Hash fallbackBlipStyleForFighter(const Fighter& fighter)
{
    PlayerRelation relation = fighterRelationToPlayer(fighter);
    if (relation == PlayerRelation::Friendly || relation == PlayerRelation::Neutral)
        return joaat("BLIP_STYLE_COMPANION");
    if (relation == PlayerRelation::Hostile)
        return joaat("BLIP_STYLE_ENEMY");
    return joaat("BLIP_STYLE_COMPANION");
}

const char* blipNameForTeam(int team)
{
    if (g_runtime.freeForAll)
        return "Battle Royale";

    switch (team)
    {
    case 0:
        return "Battle Team 1";
    case 1:
        return "Battle Team 2";
    case 2:
        return "Battle Team 3";
    case 3:
        return "Battle Team 4";
    }
    return "Battle Fighter";
}

Blip addBattleBlipForEntity(const Fighter& fighter)
{
    if (fighter.difficulty == Difficulty::Bosses)
    {
        const char* styles[] = {
            "BLIP_STYLE_BOUNTY_HUNTER",
            "BLIP_STYLE_BOUNTY_TARGET",
            "BLIP_STYLE_ENEMY"
        };

        for (const char* style : styles)
        {
            Blip blip = addBlipForEntity(joaat(style), fighter.ped);
            if (RADAR::DOES_BLIP_EXIST(blip))
                return blip;
        }
    }

    return addBlipForEntity(fallbackBlipStyleForFighter(fighter), fighter.ped);
}

void applyBlipRelationModifier(Blip blip, PlayerRelation relation)
{
    Any flashParam = 0;
    RADAR::SET_BLIP_FLASHES(blip, false, &flashParam);
    RADAR::SET_BLIP_FLASH_TIMER(blip, 0, 0);

    if (relation == PlayerRelation::Friendly)
    {
        const char* blueModifiers[] = {
            "BLIP_MODIFIER_MP_COLOR_BLUE",
            "BLIP_MODIFIER_MP_COLOR_8",
            "BLIP_MODIFIER_MP_COLOR_7",
            "BLIP_MODIFIER_COMPANION"
        };
        addFirstBlipModifier(blip, blueModifiers, static_cast<int>(sizeof(blueModifiers) / sizeof(blueModifiers[0])));
    }
    else if (relation == PlayerRelation::Hostile)
    {
        addBlipModifier(blip, "BLIP_MODIFIER_ENEMY");
    }
    else
    {
        const char* greyModifiers[] = {
            "BLIP_MODIFIER_MP_COLOR_GREY",
            "BLIP_MODIFIER_MP_COLOR_GRAY",
            "BLIP_MODIFIER_MP_COLOR_1",
            "BLIP_MODIFIER_FRIENDLY"
        };
        addFirstBlipModifier(blip, greyModifiers, static_cast<int>(sizeof(greyModifiers) / sizeof(greyModifiers[0])));
    }
}

void applyTeamBlipModifier(Blip blip, int team)
{
    applyBlipRelationModifier(blip, runtimeRelationToPlayer(team));
}

void applyFighterBlipModifier(Blip blip, const Fighter& fighter)
{
    applyBlipRelationModifier(blip, fighterRelationToPlayer(fighter));
}

void removeFighterBlip(Fighter& fighter)
{
    if (RADAR::DOES_BLIP_EXIST(fighter.blip))
        RADAR::REMOVE_BLIP(&fighter.blip);
    fighter.blip = 0;
    fighter.lastBlipUpdate = 0;
    fighter.lastBlipRelation = -1;
}

void ensureFighterBlip(Fighter& fighter)
{
    if (!exists(fighter.ped) || !isAlive(fighter))
    {
        removeFighterBlip(fighter);
        return;
    }

    bool createdBlip = false;
    if (!RADAR::DOES_BLIP_EXIST(fighter.blip))
    {
        fighter.blip = addBattleBlipForEntity(fighter);
        createdBlip = RADAR::DOES_BLIP_EXIST(fighter.blip);
    }

    if (RADAR::DOES_BLIP_EXIST(fighter.blip))
    {
        PlayerRelation relation = fighterRelationToPlayer(fighter);
        int relationValue = static_cast<int>(relation);
        DWORD t = now();
        if (!createdBlip &&
            fighter.lastBlipRelation == relationValue &&
            fighter.lastBlipUpdate != 0 &&
            t - fighter.lastBlipUpdate < kBlipRefreshMs)
        {
            return;
        }

        RADAR::SET_BLIP_SCALE(fighter.blip, fighter.difficulty == Difficulty::Bosses ? 0.68f : (relation == PlayerRelation::Hostile ? 0.58f : 0.54f));
        if (createdBlip || fighter.lastBlipRelation != relationValue)
            applyFighterBlipModifier(fighter.blip, fighter);
        RADAR::SET_BLIP_NAME_FROM_TEXT_FILE(fighter.blip, const_cast<char*>(blipNameForTeam(fighter.team)));
        fighter.lastBlipUpdate = t;
        fighter.lastBlipRelation = relationValue;
    }
}

void makePedVisible(Ped ped)
{
    if (!exists(ped))
        return;

    ENTITY::SET_ENTITY_VISIBLE(ped, true);
    ENTITY::RESET_ENTITY_ALPHA(ped);
    ENTITY::SET_ENTITY_ALPHA(ped, 255, false);
    ENTITY::SET_ENTITY_COLLISION(ped, true, true);
    invoke<Void>(0x283978A15512B2FE, ped, true);
    invoke<Void>(0xCC8CA3E88256E58F, ped, false, true, true, true, false);
}

void updatePedVariation(Ped ped)
{
    if (exists(ped))
        invoke<Void>(0xCC8CA3E88256E58F, ped, false, true, true, true, false);
}

void setPedOutfitIndex(Ped ped, int index, bool immediate)
{
    if (exists(ped) && index >= 0)
        invoke<Void>(0x77FF8D35EEC6BBC4, ped, index, immediate);
}

void applyPedOutfit(Ped ped, int index)
{
    if (!exists(ped) || index < 0)
        return;

    setPedOutfitIndex(ped, index, false);
    WAIT(0);
    setPedOutfitIndex(ped, index, true);
    updatePedVariation(ped);
    WAIT(0);
    updatePedVariation(ped);
}

Hash giveWeapon(Ped ped, const char* weaponName, bool equip)
{
    if (!exists(ped) || !weaponName || !*weaponName)
        return 0;

    Hash weapon = joaat(weaponName);
    if (!WEAPON::HAS_PED_GOT_WEAPON(ped, weapon, false, false))
        WEAPON::GIVE_DELAYED_WEAPON_TO_PED(ped, weapon, 240, equip, 0);
    WEAPON::SET_PED_INFINITE_AMMO(ped, true, weapon);
    WEAPON::SET_PED_AMMO(ped, weapon, 360);
    int maxClip = WEAPON::GET_MAX_AMMO_IN_CLIP(ped, weapon, true);
    if (maxClip > 0)
        WEAPON::SET_AMMO_IN_CLIP(ped, weapon, maxClip);
    if (equip)
        WEAPON::SET_CURRENT_PED_WEAPON(ped, weapon, true, 0, false, false);
    return weapon;
}

void giveWeaponAtAttachPoint(Ped ped, Hash weapon, int attachPoint, bool equip)
{
    if (!exists(ped) || !weapon)
        return;

    WEAPON::GIVE_DELAYED_WEAPON_TO_PED(ped, weapon, 360, equip, 0);
    WEAPON::SET_PED_INFINITE_AMMO(ped, true, weapon);
    WEAPON::SET_PED_AMMO(ped, weapon, 360);
    int maxClip = WEAPON::GET_MAX_AMMO_IN_CLIP(ped, weapon, true);
    if (maxClip > 0)
        WEAPON::SET_AMMO_IN_CLIP(ped, weapon, maxClip);
    if (equip)
        WEAPON::SET_CURRENT_PED_WEAPON(ped, weapon, true, attachPoint, false, false);
}

void ensureWeaponHash(Ped ped, Hash weapon, bool equip)
{
    if (!exists(ped) || isUnarmedWeapon(weapon))
        return;

    if (!WEAPON::HAS_PED_GOT_WEAPON(ped, weapon, false, false))
        WEAPON::GIVE_DELAYED_WEAPON_TO_PED(ped, weapon, 360, equip, 0);
    WEAPON::SET_PED_INFINITE_AMMO(ped, true, weapon);
    WEAPON::SET_PED_AMMO(ped, weapon, 360);
    int maxClip = WEAPON::GET_MAX_AMMO_IN_CLIP(ped, weapon, true);
    if (maxClip > 0)
        WEAPON::SET_AMMO_IN_CLIP(ped, weapon, maxClip);
    if (equip)
        WEAPON::SET_CURRENT_PED_WEAPON(ped, weapon, true, 0, false, false);
}

void equipMicahDualRevolvers(Ped ped, Hash primaryWeapon, bool swapWeaponTask = true)
{
    if (!exists(ped) || !primaryWeapon)
        return;

    Hash offhandWeapon = joaat("WEAPON_REVOLVER_DOUBLEACTION");
    giveWeaponAtAttachPoint(ped, primaryWeapon, kWeaponAttachDefault, true);
    giveWeaponAtAttachPoint(ped, primaryWeapon, kWeaponAttachPistolRight, true);
    giveWeaponAtAttachPoint(ped, offhandWeapon, kWeaponAttachSecondary, false);
    giveWeaponAtAttachPoint(ped, offhandWeapon, kWeaponAttachPistolLeft, false);
    WEAPON::SET_CURRENT_PED_WEAPON(ped, primaryWeapon, true, kWeaponAttachDefault, false, false);
    WEAPON::SET_CURRENT_PED_WEAPON(ped, offhandWeapon, true, kWeaponAttachSecondary, false, false);
    if (swapWeaponTask)
        AI::TASK_SWAP_WEAPON(ped, false, false, false, false);
}

bool isUnarmedWeapon(Hash weapon)
{
    return weapon == 0 || weapon == joaat("WEAPON_UNARMED");
}

void fillWeaponAmmo(Ped ped, Hash weapon)
{
    if (!exists(ped) || isUnarmedWeapon(weapon) || !WEAPON::HAS_PED_GOT_WEAPON(ped, weapon, false, false))
        return;

    WEAPON::SET_PED_INFINITE_AMMO(ped, true, weapon);
    WEAPON::SET_PED_AMMO(ped, weapon, 360);
    int maxClip = WEAPON::GET_MAX_AMMO_IN_CLIP(ped, weapon, true);
    if (maxClip > 0)
        WEAPON::SET_AMMO_IN_CLIP(ped, weapon, maxClip);
}

void debugWeaponController(const Fighter& fighter, const char* eventName, Hash desired, Hash current)
{
#if 0
    char buffer[256]{};
    std::snprintf(
        buffer,
        sizeof(buffer),
        "[BattleCreatorWeapon] %s %s desired=0x%08X current=0x%08X pending=0x%08X confirmed=0x%08X\n",
        fighter.displayName.c_str(),
        eventName ? eventName : "",
        static_cast<unsigned int>(desired),
        static_cast<unsigned int>(current),
        static_cast<unsigned int>(fighter.weaponPending),
        static_cast<unsigned int>(fighter.confirmedWeapon));
    OutputDebugStringA(buffer);
#else
    (void)fighter;
    (void)eventName;
    (void)desired;
    (void)current;
#endif
}

void debugActionState(const Fighter& fighter, const char* eventName)
{
#if 0
    char buffer[256]{};
    std::snprintf(
        buffer,
        sizeof(buffer),
        "[BattleCreatorAction] %s %s type=%d phase=%d weapon=0x%08X ammoBefore=%d retries=%d\n",
        fighter.displayName.c_str(),
        eventName ? eventName : "",
        static_cast<int>(fighter.scriptedActionType),
        static_cast<int>(fighter.dynamitePhase),
        static_cast<unsigned int>(fighter.projectileWeapon),
        fighter.projectileAmmoBefore,
        fighter.projectileTaskRetries);
    OutputDebugStringA(buffer);
#else
    (void)fighter;
    (void)eventName;
#endif
}

bool isNormalWeaponForFighter(const Fighter& fighter, Hash weapon)
{
    return !isUnarmedWeapon(weapon) &&
        (weapon == fighter.closeWeapon ||
         weapon == fighter.mediumWeapon ||
         weapon == fighter.longWeapon);
}

bool weaponControllerActive(const Fighter& fighter)
{
    return g_menu.battleType == BattleType::AllWeapons &&
        fighter.difficulty == Difficulty::Bosses &&
        (fighter.closeWeapon || fighter.mediumWeapon || fighter.longWeapon);
}

bool shouldPollManagedWeapon(const Fighter& fighter, DWORD t)
{
    return weaponControllerActive(fighter) &&
        (fighter.weaponPending ||
         fighter.temporaryWeaponOverride ||
         weaponControllerSettling(fighter, t) ||
         fighter.rangeWeaponCandidate ||
         t - fighter.lastWeaponReady > 2500u);
}

void resetWeaponController(Fighter& fighter)
{
    fighter.pendingCombatWeapon = 0;
    fighter.pendingWeaponTarget = 0;
    fighter.pendingWeaponSince = 0;
    fighter.desiredWeapon = 0;
    fighter.confirmedWeapon = 0;
    fighter.weaponPending = 0;
    fighter.weaponPendingSince = 0;
    fighter.weaponLastConfirmedAt = 0;
    fighter.weaponSettleUntil = 0;
    fighter.weaponRetryCount = 0;
    fighter.rangeWeaponCandidate = 0;
    fighter.rangeWeaponCandidateTarget = 0;
    fighter.rangeWeaponCandidateSince = 0;
    fighter.temporaryWeaponOverride = 0;
    fighter.temporaryWeaponOverrideUntil = 0;
    fighter.lastWeaponReady = 0;
    fighter.lastWeaponReadyHash = 0;
    fighter.lastWeaponSwitch = 0;
}

void disableAiWeaponSelection(Fighter& fighter)
{
    if (!exists(fighter.ped) ||
        g_menu.battleType != BattleType::AllWeapons ||
        (fighter.difficulty != Difficulty::Bosses && fighter.difficulty != Difficulty::Special))
    {
        return;
    }

    PED::SET_PED_COMBAT_ATTRIBUTES(fighter.ped, 54, false);
    PED::SET_PED_COMBAT_ATTRIBUTES(fighter.ped, 91, false);
}

Hash currentManagedWeapon(const Fighter& fighter)
{
    if (!exists(fighter.ped))
        return 0;

    Hash current{};
    if (WEAPON::GET_CURRENT_PED_WEAPON(fighter.ped, &current, true, 0, false))
        return current;
    return 0;
}

Hash currentNormalWeapon(const Fighter& fighter)
{
    Hash current = currentManagedWeapon(fighter);
    return isNormalWeaponForFighter(fighter, current) ? current : 0;
}

void confirmManagedWeaponIfEquipped(Fighter& fighter, DWORD t)
{
    Hash current = currentNormalWeapon(fighter);
    if (!current)
        return;

    fighter.confirmedWeapon = current;
    fighter.combatWeapon = current;
    fighter.desiredWeapon = current;
    fighter.lastWeaponReady = t;
    fighter.lastWeaponReadyHash = current;

    if (fighter.weaponPending == current)
    {
        fighter.weaponPending = 0;
        fighter.weaponPendingSince = 0;
        fighter.weaponRetryCount = 0;
        fighter.weaponLastConfirmedAt = t;
        fighter.lastWeaponSwitch = t;
        fighter.weaponSettleUntil = t + kWeaponSettleMs;
        debugWeaponController(fighter, "confirmed", current, current);
    }
}

bool hasTemporaryWeaponOverride(Fighter& fighter, DWORD t)
{
    if (!fighter.temporaryWeaponOverride)
        return false;

    if (fighter.temporaryWeaponOverrideUntil != 0 && t > fighter.temporaryWeaponOverrideUntil)
    {
        fighter.temporaryWeaponOverride = 0;
        fighter.temporaryWeaponOverrideUntil = 0;
        return false;
    }

    return true;
}

void beginTemporaryWeaponOverride(Fighter& fighter, Hash weapon, DWORD t, DWORD durationMs)
{
    fighter.temporaryWeaponOverride = weapon;
    fighter.temporaryWeaponOverrideUntil = durationMs == 0 ? 0 : t + durationMs;
    fighter.weaponPending = 0;
    fighter.weaponPendingSince = 0;
    fighter.weaponRetryCount = 0;
    fighter.weaponSettleUntil = 0;
    fighter.rangeWeaponCandidate = 0;
    fighter.rangeWeaponCandidateTarget = 0;
    fighter.rangeWeaponCandidateSince = 0;
}

void clearTemporaryWeaponOverride(Fighter& fighter)
{
    fighter.temporaryWeaponOverride = 0;
    fighter.temporaryWeaponOverrideUntil = 0;
}

void resetScriptedActionState(Fighter& fighter, bool clearTemporaryOverride = true)
{
    fighter.scriptedActionType = ScriptedActionType::None;
    fighter.dynamitePhase = DynamitePhase::None;
    fighter.scriptedActionStartedAt = 0;
    fighter.scriptedActionResumeAt = 0;
    fighter.scriptedActionTimeoutAt = 0;
    fighter.projectileWeapon = 0;
    fighter.projectileRestoreWeapon = 0;
    fighter.projectileTarget = 0;
    fighter.projectileThrowPos = {};
    fighter.projectileAmmoBefore = -1;
    fighter.projectileTaskIssued = false;
    fighter.projectileTaskObservedActive = false;
    fighter.projectileReleaseConfirmed = false;
    fighter.projectileTaskRetries = 0;
    fighter.projectileEquipRequestedAt = 0;
    fighter.projectileTaskRequestedAt = 0;
    fighter.projectileCommittedAt = 0;
    fighter.evasionStartPos = {};
    fighter.evasionTargetPos = {};
    fighter.evasionStyle = BossEvasionStyle::None;
    fighter.evasionTaskRequested = false;
    fighter.evasionActuallyStarted = false;
    fighter.evasionFinished = false;
    fighter.evasionDeadEyeSuppressed = false;
    fighter.evasionShotsObserved = false;
    fighter.evasionPlayerTriggered = false;
    fighter.evasionShootDuringDash = true;
    fighter.evasionVelocityFallbackApplied = false;
    fighter.evasionFallbackAttempts = 0;
    fighter.evasionThreat = 0;
    fighter.evasionAimTarget = 0;
    fighter.evasionFiringTarget = 0;
    fighter.evasionSideX = 0.0f;
    fighter.evasionSideY = 0.0f;
    fighter.evasionBackX = 0.0f;
    fighter.evasionBackY = 0.0f;
    fighter.evasionSideSign = 0.0f;
    fighter.evasionTaskSpeed = 0.0f;
    fighter.evasionDashDurationMs = 0;
    fighter.evasionRequestedAt = 0;
    fighter.evasionStartedAt = 0;
    fighter.evasionExpectedEndAt = 0;
    fighter.evasionDeadEyeBlockStartedAt = 0;
    fighter.evasionDeadEyeBlockUntil = 0;
    fighter.evasionFollowUpAt = 0;

    if (clearTemporaryOverride)
    {
        fighter.temporaryWeaponOverride = 0;
        fighter.temporaryWeaponOverrideUntil = 0;
        fighter.weaponPending = 0;
        fighter.weaponPendingSince = 0;
        fighter.weaponRetryCount = 0;
        fighter.weaponSettleUntil = 0;
    }
}

bool protectedScriptedActionActive(const Fighter& fighter)
{
    return fighter.scriptedActionType == ScriptedActionType::DynamiteThrow ||
        fighter.scriptedActionType == ScriptedActionType::BossEvasion;
}

bool projectileActionActive(const Fighter& fighter)
{
    return fighter.scriptedActionType == ScriptedActionType::DynamiteThrow &&
        fighter.dynamitePhase != DynamitePhase::None;
}

void extendTemporaryWeaponOverride(Fighter& fighter, Hash weapon, DWORD t, DWORD durationMs)
{
    fighter.temporaryWeaponOverride = weapon;
    fighter.temporaryWeaponOverrideUntil = std::max(fighter.temporaryWeaponOverrideUntil, t + durationMs);
}

bool weaponControllerSettling(const Fighter& fighter, DWORD t)
{
    return fighter.weaponSettleUntil != 0 && t < fighter.weaponSettleUntil;
}

bool requestTemporaryWeaponEquip(Fighter& fighter, Hash desired, DWORD t, int ammo, const char* reason)
{
    if (!exists(fighter.ped) || isUnarmedWeapon(desired))
        return false;

    if (!WEAPON::HAS_PED_GOT_WEAPON(fighter.ped, desired, false, false))
        WEAPON::GIVE_DELAYED_WEAPON_TO_PED(fighter.ped, desired, ammo, false, 0);
    WEAPON::SET_PED_AMMO(fighter.ped, desired, ammo);

    Hash current = currentManagedWeapon(fighter);
    if (current == desired)
    {
        fighter.weaponPending = 0;
        fighter.weaponPendingSince = 0;
        fighter.weaponRetryCount = 0;
        fighter.lastWeaponReady = t;
        fighter.lastWeaponReadyHash = desired;
        return !weaponControllerSettling(fighter, t);
    }

    if (fighter.weaponPending == desired)
    {
        if (t - fighter.weaponPendingSince < kWeaponPendingTimeoutMs)
            return false;

        if (fighter.weaponRetryCount >= kWeaponMaxRetries)
        {
            debugWeaponController(fighter, "temp-equip-failed", desired, current);
            return false;
        }

        ++fighter.weaponRetryCount;
        fighter.weaponPendingSince = t;
        debugWeaponController(fighter, "temp-equip-retry", desired, current);
    }
    else
    {
        fighter.weaponPending = desired;
        fighter.weaponPendingSince = t;
        fighter.weaponRetryCount = 0;
        debugWeaponController(fighter, reason ? reason : "temp-equip", desired, current);
    }

    WEAPON::SET_CURRENT_PED_WEAPON(fighter.ped, desired, true, 0, false, false);
    fighter.lastWeaponReady = t;
    fighter.lastWeaponReadyHash = desired;
    fighter.weaponSettleUntil = t + kProjectileEquipSettleMs;
    return false;
}

bool requestManagedWeapon(Fighter& fighter, Hash desired, DWORD t, bool force, const char* reason)
{
    if (!weaponControllerActive(fighter) || isUnarmedWeapon(desired) || !exists(fighter.ped))
        return false;

    if (shouldPollManagedWeapon(fighter, t))
        confirmManagedWeaponIfEquipped(fighter, t);

    if (hasTemporaryWeaponOverride(fighter, t) && fighter.temporaryWeaponOverride != desired)
        return false;

    ensureWeaponHash(fighter.ped, desired, false);
    fillWeaponAmmo(fighter.ped, desired);

    Hash current = currentManagedWeapon(fighter);
    if (current == desired)
    {
        fighter.confirmedWeapon = desired;
        fighter.combatWeapon = desired;
        fighter.desiredWeapon = desired;
        fighter.weaponPending = 0;
        fighter.weaponPendingSince = 0;
        fighter.weaponRetryCount = 0;
        fighter.lastWeaponReady = t;
        fighter.lastWeaponReadyHash = desired;
        return false;
    }

    if (!force && weaponControllerSettling(fighter, t))
        return false;

    if (fighter.weaponPending == desired)
    {
        if (t - fighter.weaponPendingSince < kWeaponPendingTimeoutMs)
            return false;

        if (fighter.weaponRetryCount >= kWeaponMaxRetries)
        {
            debugWeaponController(fighter, "failed", desired, current);
            fighter.weaponPending = 0;
            fighter.weaponPendingSince = 0;
            fighter.weaponRetryCount = 0;
            if (isNormalWeaponForFighter(fighter, current))
                fighter.combatWeapon = current;
            return false;
        }

        ++fighter.weaponRetryCount;
        fighter.weaponPendingSince = t;
        debugWeaponController(fighter, "retry", desired, current);
    }
    else
    {
        if (!force && t - fighter.weaponLastConfirmedAt < kWeaponSwitchCooldownMs)
            return false;

        fighter.weaponPending = desired;
        fighter.weaponPendingSince = t;
        fighter.weaponRetryCount = 0;
        debugWeaponController(fighter, reason ? reason : "request", desired, current);
    }

    fighter.desiredWeapon = desired;
    fighter.combatWeapon = desired;
    WEAPON::SET_CURRENT_PED_WEAPON(fighter.ped, desired, true, 0, false, false);
    fighter.lastWeaponReady = t;
    fighter.lastWeaponReadyHash = desired;
    fighter.weaponSettleUntil = t + kWeaponSettleMs;
    return true;
}

Hash currentOrBestPedWeapon(Ped ped)
{
    if (!exists(ped))
        return 0;

    Hash current{};
    if (WEAPON::GET_CURRENT_PED_WEAPON(ped, &current, true, 0, false) && !isUnarmedWeapon(current))
        return current;

    Hash best = WEAPON::GET_BEST_PED_WEAPON(ped, false, true);
    if (!isUnarmedWeapon(best) && WEAPON::HAS_PED_GOT_WEAPON(ped, best, false, false))
        return best;

    return 0;
}

template <size_t N>
const char* chooseFromArray(const std::array<const char*, N>& values, int seed, const char* fallback)
{
    for (size_t attempt = 0; attempt < values.size(); ++attempt)
    {
        const char* value = values[(static_cast<size_t>(std::max(seed, 0)) + attempt) % values.size()];
        if (value && *value)
            return value;
    }
    return fallback;
}

const char* fallbackFirearmForSlot(const TeamRosterSlot& slot)
{
    if (slot.difficulty == Difficulty::Bosses)
        return "WEAPON_REVOLVER_CATTLEMAN";

    if (slot.difficulty == Difficulty::Special)
    {
        if (slot.special == kSpecialCharles)
            return "WEAPON_BOW";
        if (slot.special == kSpecialTommy)
            return "WEAPON_SHOTGUN_DOUBLEBARREL";
        return "WEAPON_REVOLVER_CATTLEMAN";
    }

    if (slot.pedSet >= static_cast<int>(kDefaultPedSets.size()) && slot.pedSet < static_cast<int>(g_pedSets.size()))
        return chooseFromArray(g_pedSets[static_cast<size_t>(slot.pedSet)].firearms, 0, "WEAPON_REVOLVER_CATTLEMAN");

    switch (slot.pedSet)
    {
    case 0:
    case 1:
    case 2:
    case 3:
    case 8:
    case 9:
    case kNamedGangPedSetIndex:
    case kMicahsGangPedSetIndex:
        return "WEAPON_REPEATER_CARBINE";
    default:
        return "WEAPON_REVOLVER_CATTLEMAN";
    }
}

void giveBossGunLoadout(Ped ped, const TeamRosterSlot& slot, Hash& closeWeapon, Hash& mediumWeapon, Hash& longWeapon)
{
    closeWeapon = 0;
    mediumWeapon = 0;
    longWeapon = 0;

    if (!exists(ped) || slot.difficulty != Difficulty::Bosses || g_menu.battleType != BattleType::AllWeapons)
        return;

    if (slot.boss == kBossMicah)
    {
        Hash micahRevolver = giveWeapon(ped, "WEAPON_REVOLVER_DOUBLEACTION_MICAH", false);
        Hash backupRevolver = giveWeapon(ped, "WEAPON_REVOLVER_DOUBLEACTION", false);
        mediumWeapon = micahRevolver ? micahRevolver : backupRevolver;
        closeWeapon = mediumWeapon;
        longWeapon = mediumWeapon;
        if (mediumWeapon)
            equipMicahDualRevolvers(ped, mediumWeapon);
        return;
    }

    if (slot.boss == kBossDutch)
    {
        closeWeapon = giveWeapon(ped, "WEAPON_REVOLVER_SCHOFIELD", false);
        mediumWeapon = giveWeapon(ped, "WEAPON_RIFLE_BOLTACTION", false);
        longWeapon = mediumWeapon;
    }
    else if (slot.boss == kBossColm)
    {
        Hash defaultWeapon = currentOrBestPedWeapon(ped);
        if (!defaultWeapon)
            defaultWeapon = giveWeapon(ped, "WEAPON_REVOLVER_CATTLEMAN", false);
        closeWeapon = defaultWeapon;
        mediumWeapon = defaultWeapon;
        longWeapon = defaultWeapon;
    }
    else
    {
        closeWeapon = giveWeapon(ped, "WEAPON_SHOTGUN_DOUBLEBARREL", false);
        mediumWeapon = giveWeapon(ped, "WEAPON_REPEATER_CARBINE", false);
        longWeapon = giveWeapon(ped, "WEAPON_RIFLE_BOLTACTION", false);
    }

    if (mediumWeapon)
        WEAPON::SET_CURRENT_PED_WEAPON(ped, mediumWeapon, true, 0, false, false);
}

bool giveSpecialGunLoadout(Ped ped, const TeamRosterSlot& slot, Hash& closeWeapon, Hash& mediumWeapon, Hash& longWeapon)
{
    closeWeapon = 0;
    mediumWeapon = 0;
    longWeapon = 0;

    if (!exists(ped) || slot.difficulty != Difficulty::Special || g_menu.battleType != BattleType::AllWeapons)
        return false;

    if (slot.special == kSpecialTommy)
    {
        closeWeapon = giveWeapon(ped, "WEAPON_MELEE_HATCHET", false);
        mediumWeapon = giveWeapon(ped, "WEAPON_SHOTGUN_DOUBLEBARREL", false);
        longWeapon = giveWeapon(ped, "WEAPON_REPEATER_CARBINE", false);
        if (mediumWeapon)
            WEAPON::SET_CURRENT_PED_WEAPON(ped, mediumWeapon, true, 0, false, false);
        return closeWeapon || mediumWeapon || longWeapon;
    }

    if (slot.special == kSpecialCharles)
    {
        closeWeapon = giveWeapon(ped, "WEAPON_THROWN_THROWING_KNIVES", false);
        mediumWeapon = giveWeapon(ped, "WEAPON_THROWN_TOMAHAWK", false);
        longWeapon = giveWeapon(ped, "WEAPON_BOW", false);
        if (longWeapon)
            WEAPON::SET_CURRENT_PED_WEAPON(ped, longWeapon, true, 0, false, false);
        return closeWeapon || mediumWeapon || longWeapon;
    }

    return false;
}

Hash applyBattleWeapons(Ped ped, const TeamRosterSlot& slot, int seed, Hash* closeWeapon = nullptr, Hash* mediumWeapon = nullptr, Hash* longWeapon = nullptr)
{
    if (!exists(ped))
        return 0;

    if (g_menu.battleType == BattleType::NoWeapons)
    {
        WEAPON::REMOVE_ALL_PED_WEAPONS(ped, true, true);
        WEAPON::SET_CURRENT_PED_WEAPON(ped, joaat("WEAPON_UNARMED"), true, 0, false, false);
        return joaat("WEAPON_UNARMED");
    }

    if (g_menu.battleType == BattleType::MeleeOnly)
    {
        WEAPON::REMOVE_ALL_PED_WEAPONS(ped, true, true);
        const char* weaponName =
            (slot.difficulty == Difficulty::Extreme ||
             slot.difficulty == Difficulty::Special ||
             slot.difficulty == Difficulty::Bosses) ?
            "WEAPON_MELEE_MACHETE" :
            "WEAPON_MELEE_KNIFE";
        Hash meleeWeapon = giveWeapon(ped, weaponName, true);
        if (closeWeapon)
            *closeWeapon = meleeWeapon;
        if (mediumWeapon)
            *mediumWeapon = meleeWeapon;
        if (longWeapon)
            *longWeapon = meleeWeapon;
        if (!isUnarmedWeapon(meleeWeapon))
            WEAPON::SET_CURRENT_PED_WEAPON(ped, meleeWeapon, true, 0, false, false);
        return meleeWeapon;
    }

    if (slot.difficulty == Difficulty::Bosses)
    {
        Hash close{};
        Hash medium{};
        Hash longRange{};
        giveBossGunLoadout(ped, slot, close, medium, longRange);
        if (closeWeapon)
            *closeWeapon = close;
        if (mediumWeapon)
            *mediumWeapon = medium;
        if (longWeapon)
            *longWeapon = longRange;
        return medium ? medium : currentOrBestPedWeapon(ped);
    }

    if (slot.difficulty == Difficulty::Special)
    {
        Hash close{};
        Hash medium{};
        Hash longRange{};
        if (giveSpecialGunLoadout(ped, slot, close, medium, longRange))
        {
            if (closeWeapon)
                *closeWeapon = close;
            if (mediumWeapon)
                *mediumWeapon = medium;
            if (longWeapon)
                *longWeapon = longRange;
            return longRange ? longRange : (medium ? medium : close);
        }
    }

    Hash defaultWeapon = currentOrBestPedWeapon(ped);
    if (defaultWeapon)
    {
        fillWeaponAmmo(ped, defaultWeapon);
        return defaultWeapon;
    }

    return giveWeapon(ped, fallbackFirearmForSlot(slot), true);
}

float combatSightRangeForFighter(const Fighter& fighter)
{
    switch (fighter.difficulty)
    {
    case Difficulty::Easy:
        return 48.0f;
    case Difficulty::Medium:
        return 62.0f;
    case Difficulty::Hard:
        return 88.0f;
    case Difficulty::Extreme:
        return 108.0f;
    case Difficulty::Special:
        if (fighter.special == kSpecialJavier)
            return 138.0f;
        if (fighter.special == kSpecialTommy)
            return 82.0f;
        if (fighter.special == kSpecialCharles)
            return 138.0f;
        return 96.0f;
    case Difficulty::Bosses:
        if (fighter.boss == kBossDutch)
            return 158.0f;
        if (fighter.boss == kBossMicah)
            return 112.0f;
        if (fighter.boss == kBossColm)
            return 118.0f;
        if (fighter.boss == kBossJohn || fighter.boss == kBossArthur)
            return 158.0f;
        return 132.0f;
    }
    return 70.0f;
}

float preferredGunRangeForFighter(const Fighter& fighter)
{
    switch (fighter.difficulty)
    {
    case Difficulty::Easy:
        return 18.0f;
    case Difficulty::Medium:
        return 24.0f;
    case Difficulty::Hard:
        return 30.0f;
    case Difficulty::Extreme:
        return 34.0f;
    case Difficulty::Special:
        if (fighter.special == kSpecialJavier)
            return 40.0f;
        if (fighter.special == kSpecialTommy)
            return 9.0f;
        if (fighter.special == kSpecialCharles)
            return 50.0f;
        return 34.0f;
    case Difficulty::Bosses:
        if (fighter.boss == kBossMicah)
            return 24.0f;
        if (fighter.boss == kBossDutch)
            return 68.0f;
        if (fighter.boss == kBossColm)
            return 42.0f;
        if (fighter.boss == kBossJohn || fighter.boss == kBossArthur)
            return 62.0f;
        return 48.0f;
    }
    return 30.0f;
}

float combatMoveSpeedForFighter(const Fighter& fighter)
{
    float speed = 1.35f;
    switch (fighter.difficulty)
    {
    case Difficulty::Easy:
        speed = 1.78f;
        break;
    case Difficulty::Medium:
        speed = 1.92f;
        break;
    case Difficulty::Hard:
        speed = 2.08f;
        break;
    case Difficulty::Extreme:
        speed = 2.35f;
        break;
    case Difficulty::Special:
        if (fighter.special == kSpecialJavier)
            speed = 3.05f;
        else if (fighter.special == kSpecialTommy)
            speed = 2.55f;
        else if (fighter.special == kSpecialCharles)
            speed = 2.55f;
        else
            speed = 1.55f;
        break;
    case Difficulty::Bosses:
        if (fighter.boss == kBossMicah)
            speed = 2.55f;
        else if (fighter.boss == kBossDutch)
            speed = 1.85f;
        else if (fighter.boss == kBossColm)
            speed = 1.75f;
        else if (fighter.boss == kBossJohn || fighter.boss == kBossArthur)
            speed = 2.90f;
        else
            speed = 2.25f;
        break;
    }
    return std::clamp(speed * g_settings.combatMoveSpeedMultiplier, 0.5f, 4.0f);
}

bool shouldProtectCinematicKills(const Fighter& fighter)
{
    if (fighter.difficulty == Difficulty::Extreme || fighter.difficulty == Difficulty::Special)
        return true;

    if (fighter.difficulty == Difficulty::Bosses)
        return true;

    return false;
}

void debugProtectedHeadshotMultiplierTest(
    const Fighter& fighter,
    const char* reason,
    int previousHealth,
    int currentHealth,
    bool cinematicRecoveryTriggered)
{
#if BATTLECREATOR_ENABLE_HEADSHOT_MULTIPLIER_DIAGNOSTICS
    if (!exists(fighter.ped) || !shouldProtectCinematicKills(fighter))
        return;

    char buffer[512];
    std::snprintf(
        buffer,
        sizeof(buffer),
        "[BattleCreator][HeadshotTest] %s name=%s difficulty=%d ped=%d multiplier=%.2f health=%d->%d entityDead=%d pedDead=%d fatal=%d cinematicRecovery=%d\n",
        reason ? reason : "event",
        fighter.displayName.empty() ? "unknown" : fighter.displayName.c_str(),
        static_cast<int>(fighter.difficulty),
        static_cast<int>(fighter.ped),
        kProtectedHeadshotTestMultiplier,
        previousHealth,
        currentHealth,
        ENTITY::IS_ENTITY_DEAD(fighter.ped) ? 1 : 0,
        PED::IS_PED_DEAD_OR_DYING(fighter.ped, true) ? 1 : 0,
        PED::IS_PED_FATALLY_INJURED(fighter.ped) ? 1 : 0,
        cinematicRecoveryTriggered ? 1 : 0);
    OutputDebugStringA(buffer);
#else
    (void)fighter;
    (void)reason;
    (void)previousHealth;
    (void)currentHealth;
    (void)cinematicRecoveryTriggered;
#endif
}

void applyProtectedHeadshotMultiplierTest(Fighter& fighter, const char* reason)
{
    if (!exists(fighter.ped) || !shouldProtectCinematicKills(fighter))
        return;

    PED::SET_PED_CONFIG_FLAG(fighter.ped, kPedConfigFlagProtectedNoCriticalHits, true);
    PED::SET_PED_CONFIG_FLAG(fighter.ped, kPedConfigFlagDisableHeadGore, true);
    PED::SET_PED_CONFIG_FLAG(fighter.ped, kPedConfigFlagDisableLimbGore, true);
    PED::_0x2BA918C823B8BA56(fighter.ped, kProtectedHeadshotTestMultiplier);
    debugProtectedHeadshotMultiplierTest(
        fighter,
        reason,
        ENTITY::GET_ENTITY_HEALTH(fighter.ped),
        ENTITY::GET_ENTITY_HEALTH(fighter.ped),
        fighter.cinematicRecoveryActive);
}

void applyProtectedExecutionActionDisables(Fighter& fighter, const char* reason)
{
    if (!exists(fighter.ped) || !shouldProtectCinematicKills(fighter))
        return;

    PED::_0xC163DAC52AC975D3(fighter.ped, kActionFailedTakedown);
    PED::_0xC163DAC52AC975D3(fighter.ped, kActionTakedown);
    PED::_0xC163DAC52AC975D3(fighter.ped, kActionExecution);
    PED::_0xC163DAC52AC975D3(fighter.ped, kActionStealthKill);
    (void)reason;
}

void applyProtectedExecutionResetFlags(Fighter& fighter, int health, bool dead)
{
    if (!exists(fighter.ped) ||
        !shouldProtectCinematicKills(fighter) ||
        dead ||
        health <= 0)
    {
        return;
    }

    PED::SET_PED_RESET_FLAG(fighter.ped, kPedResetFlagSuppressLethalMeleeActions, true);
    PED::SET_PED_RESET_FLAG(fighter.ped, kPedResetFlagPreventAllMeleeTakedowns, true);
    PED::SET_PED_RESET_FLAG(fighter.ped, kPedResetFlagPreventFailedMeleeTakedowns, true);
}

void recordProtectedExecutionFallback(Fighter& fighter, const char* reason, DWORD t)
{
    if (!exists(fighter.ped) || !shouldProtectCinematicKills(fighter))
        return;

    ++g_runtime.protectedExecutionFallbacks;

#if BATTLECREATOR_ENABLE_EXECUTION_PREVENTION_DIAGNOSTICS
    char buffer[512];
    std::snprintf(
        buffer,
        sizeof(buffer),
        "[BattleCreator][ExecutionPreventionTest] fallback=%d reason=%s name=%s difficulty=%d ped=%d health=%d lastHealth=%d stealth=%d dead=%d ragdoll=%d t=%lu\n",
        g_runtime.protectedExecutionFallbacks,
        reason ? reason : "unknown",
        fighter.displayName.empty() ? "unknown" : fighter.displayName.c_str(),
        static_cast<int>(fighter.difficulty),
        static_cast<int>(fighter.ped),
        ENTITY::GET_ENTITY_HEALTH(fighter.ped),
        fighter.lastHealth,
        PED::IS_PED_BEING_STEALTH_KILLED(fighter.ped) ? 1 : 0,
        PED::IS_PED_DEAD_OR_DYING(fighter.ped, true) ? 1 : 0,
        (PED::IS_PED_RAGDOLL(fighter.ped) || PED::IS_PED_RUNNING_RAGDOLL_TASK(fighter.ped)) ? 1 : 0,
        static_cast<unsigned long>(t));
    OutputDebugStringA(buffer);
#else
    (void)reason;
    (void)t;
#endif
}

bool shouldUseNativeCriticalProtection(const Fighter& fighter, int health, bool dead)
{
    if (!shouldProtectCinematicKills(fighter) || dead || health <= 0)
        return false;

    int threshold = executionHealthThreshold(fighter);
    if (threshold <= 0)
        return true;

    return health > threshold;
}

void setFighterCriticalHitsAllowed(Fighter& fighter, bool allowed)
{
    if (!exists(fighter.ped))
        return;

    PED::SET_PED_CONFIG_FLAG(fighter.ped, kPedConfigFlagNoCriticalHits, !allowed);
}

void applyNativeCriticalProtection(Fighter& fighter, int health, bool dead)
{
    if (!exists(fighter.ped))
        return;

    bool blockCriticals = shouldUseNativeCriticalProtection(fighter, health, dead);
    setFighterCriticalHitsAllowed(fighter, !blockCriticals);
}

bool shouldBlockExecutionsByThreshold(const Fighter& fighter, int health, bool dead)
{
    if (!shouldProtectCinematicKills(fighter) || dead || health <= 0)
        return false;

    int threshold = executionHealthThreshold(fighter);
    if (threshold <= 0)
        return true;

    return health > threshold;
}

void applyExecutionThresholdProtection(Fighter& fighter, int health, bool dead)
{
    if (!exists(fighter.ped))
        return;

    bool blockExecutions = shouldBlockExecutionsByThreshold(fighter, health, dead);
    setFighterCriticalHitsAllowed(fighter, !blockExecutions);

    if (kUsePersistentExecutionActionDisable && blockExecutions)
        applyProtectedExecutionActionDisables(fighter, "threshold-update");
    if (blockExecutions)
        applyProtectedExecutionResetFlags(fighter, health, dead);

    bool emergencyInvincible = fighter.cinematicRecoveryActive ||
        (blockExecutions && PED::IS_PED_BEING_STEALTH_KILLED(fighter.ped));
    ENTITY::SET_ENTITY_INVINCIBLE(fighter.ped, emergencyInvincible);
}

DWORD approachDelayForFighter(const Fighter& fighter)
{
    if (fighter.difficulty == Difficulty::Special)
        return kSpecialPeds[static_cast<size_t>(fighter.special)].approachDelayMs;
    if (fighter.difficulty == Difficulty::Bosses)
        return kBosses[static_cast<size_t>(fighter.boss)].approachDelayMs;

    switch (fighter.difficulty)
    {
    case Difficulty::Easy:
    case Difficulty::Medium:
    case Difficulty::Hard:
    case Difficulty::Extreme:
    case Difficulty::Special:
    case Difficulty::Bosses:
        return kDifficulty[static_cast<size_t>(difficultyIndex(fighter.difficulty))].approachDelayMs;
    }
    return kDifficulty[static_cast<size_t>(difficultyIndex(fighter.difficulty))].approachDelayMs;
}

int bossShootRate(const Fighter& fighter)
{
    if (fighter.difficulty != Difficulty::Bosses)
        return kDifficulty[static_cast<size_t>(difficultyIndex(fighter.difficulty))].shootRate;

    return kBosses[static_cast<size_t>(fighter.boss)].shootRate;
}

int bossShotDuration(const Fighter& fighter, bool woundedBoss)
{
    const BossDef& boss = kBosses[static_cast<size_t>(fighter.boss)];
    return woundedBoss ? boss.woundedShotDurationMs : boss.shotDurationMs;
}

int bossNativeCombatMovement(const Fighter& fighter)
{
    return fighter.boss == kBossDutch ||
        fighter.boss == kBossColm ||
        fighter.boss == kBossJohn ||
        fighter.boss == kBossArthur ? 2 : 3;
}

float bossBurstRangeBonus(const Fighter& fighter)
{
    switch (fighter.boss)
    {
    case kBossMicah:
        return 8.0f;
    case kBossDutch:
        return 18.0f;
    case kBossColm:
        return 12.0f;
    case kBossJohn:
    case kBossArthur:
        return 24.0f;
    default:
        return 14.0f;
    }
}

void applyStaticPedTuning(Fighter& fighter)
{
    if (!exists(fighter.ped))
        return;

    const DifficultyTuning& tuning = kDifficulty[static_cast<size_t>(difficultyIndex(fighter.difficulty))];

    ENTITY::SET_ENTITY_MAX_HEALTH(fighter.ped, fighter.maxHealth);
    PED::SET_PED_MAX_HEALTH(fighter.ped, fighter.maxHealth);
    ENTITY::SET_ENTITY_CAN_BE_DAMAGED(fighter.ped, true);
    ENTITY::SET_ENTITY_INVINCIBLE(fighter.ped, false);
    PED::SET_PED_RELATIONSHIP_GROUP_DEFAULT_HASH(fighter.ped, fighter.group);
    PED::SET_PED_RELATIONSHIP_GROUP_HASH(fighter.ped, fighter.group);
    applyDamagePermissions(fighter);
    WEAPON::SET_PED_DROPS_WEAPONS_WHEN_DEAD(fighter.ped, false);
    PED::SET_PED_FLEE_ATTRIBUTES(fighter.ped, 0, false);
    PED::SET_PED_KEEP_TASK(fighter.ped, true);
    PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(fighter.ped, true);

    PED::SET_PED_ACCURACY(fighter.ped, randomRange(tuning.minAccuracy, tuning.maxAccuracy));
    PED::SET_PED_SHOOT_RATE(fighter.ped, tuning.shootRate);
    PED::SET_PED_COMBAT_ABILITY(fighter.ped, tuning.combatAbility);
    PED::SET_PED_COMBAT_MOVEMENT(fighter.ped, tuning.combatMovement);
    PED::SET_PED_COMBAT_RANGE(fighter.ped, tuning.combatRange);
    PED::SET_PED_TARGET_LOSS_RESPONSE(fighter.ped, 1);
    float moveRate = std::clamp(tuning.moveRate * g_settings.combatMoveSpeedMultiplier, 0.1f, 5.0f);
    PED::SET_PED_MOVE_RATE_OVERRIDE(fighter.ped, moveRate);
    PED::SET_PED_MAX_MOVE_BLEND_RATIO(fighter.ped, moveRate);
    float sightRange = combatSightRangeForFighter(fighter);
    PED::SET_PED_SEEING_RANGE(fighter.ped, sightRange);
    PED::SET_PED_HEARING_RANGE(fighter.ped, sightRange + 18.0f);
    if (fighter.difficulty == Difficulty::Special || fighter.difficulty == Difficulty::Bosses)
    {
        const int advancedAttributes[] = { 1, 2, 5, 13, 17, 20, 21, 28, 34, 38, 46, 50, 54 };
        for (int attribute : advancedAttributes)
            PED::SET_PED_COMBAT_ATTRIBUTES(fighter.ped, attribute, true);
    }
    if (fighter.hardened)
    {
        PED::SET_PED_COMBAT_ABILITY(fighter.ped, tuning.combatAbility);
        PED::SET_PED_COMBAT_MOVEMENT(fighter.ped, tuning.combatMovement);
        PED::SET_PED_COMBAT_RANGE(fighter.ped, tuning.combatRange);
        PED::SET_PED_TARGET_LOSS_RESPONSE(fighter.ped, 1);
        PED::SET_PED_SEEING_RANGE(fighter.ped, sightRange);
        PED::SET_PED_HEARING_RANGE(fighter.ped, sightRange + 22.0f);
        bool eliteFighter =
            fighter.difficulty == Difficulty::Special ||
            fighter.difficulty == Difficulty::Bosses;
        if (eliteFighter)
            PED::SET_PED_FIRING_PATTERN(fighter.ped, joaat("FIRING_PATTERN_FULL_AUTO"));
        if (fighter.difficulty == Difficulty::Bosses && g_menu.battleType == BattleType::NoWeapons)
            setPedActionMode(fighter.ped, true);
        if (fighter.difficulty == Difficulty::Special &&
            g_menu.battleType != BattleType::AllWeapons &&
            kSpecialPeds[static_cast<size_t>(fighter.special)].meleeSpecialist)
        {
            setPedActionMode(fighter.ped, true);
        }
        PED::SET_PED_CAN_RAGDOLL(fighter.ped, false);
        PED::SET_PED_CAN_RAGDOLL_FROM_PLAYER_IMPACT(fighter.ped, false);
        PED::SET_PED_RAGDOLL_ON_COLLISION(fighter.ped, false, 0);
        PED::_SET_PED_RAGDOLL_BLOCKING_FLAGS(fighter.ped, 0xFFFFFFFF);
        PED::SET_PED_CAN_BE_TARGETTED(fighter.ped, true);
        PED::SET_PED_CAN_BE_TARGETTED_BY_PLAYER(fighter.ped, PLAYER::PLAYER_ID(), true);
        if (eliteFighter)
        {
            const int eliteAttributes[] = { 0, 1, 2, 3, 5, 12, 13, 17, 20, 21, 27, 28, 31, 34, 38, 41, 46, 50, 54, 58 };
            for (int attribute : eliteAttributes)
                PED::SET_PED_COMBAT_ATTRIBUTES(fighter.ped, attribute, true);
            PED::SET_PED_CONFIG_FLAG(fighter.ped, 279, true);
            PED::SET_PED_CONFIG_FLAG(fighter.ped, 297, true);
            PED::SET_PED_CONFIG_FLAG(fighter.ped, 301, false);
        }
    }
    else
    {
        PED::SET_PED_CAN_RAGDOLL(fighter.ped, true);
        PED::SET_PED_CAN_RAGDOLL_FROM_PLAYER_IMPACT(fighter.ped, true);
        PED::SET_PED_RAGDOLL_ON_COLLISION(fighter.ped, true, 0);
        PED::_RESET_PED_RAGDOLL_BLOCKING_FLAGS(fighter.ped, 0xFFFFFFFF);
    }

    if (fighter.difficulty == Difficulty::Special)
    {
        const SpecialPedDef& special = kSpecialPeds[static_cast<size_t>(fighter.special)];
        PED::SET_PED_ACCURACY(fighter.ped, randomRange(special.minAccuracy, special.maxAccuracy));
        PED::SET_PED_SHOOT_RATE(fighter.ped, special.shootRate);
        PED::SET_PED_COMBAT_ABILITY(fighter.ped, 2);
        PED::SET_PED_COMBAT_MOVEMENT(fighter.ped, special.combatMovement);
        PED::SET_PED_COMBAT_RANGE(fighter.ped, special.combatRange);
        PED::SET_PED_SEEING_RANGE(fighter.ped, sightRange);
        PED::SET_PED_HEARING_RANGE(fighter.ped, sightRange + 18.0f);
        float specialMoveRate = std::clamp(special.moveRate * g_settings.combatMoveSpeedMultiplier, 0.1f, 5.0f);
        PED::SET_PED_MOVE_RATE_OVERRIDE(fighter.ped, specialMoveRate);
        PED::SET_PED_MAX_MOVE_BLEND_RATIO(fighter.ped, specialMoveRate);
    }

    if (fighter.difficulty == Difficulty::Bosses)
    {
        const BossDef& boss = kBosses[static_cast<size_t>(fighter.boss)];
        float bossMoveRate = std::clamp(boss.moveRate * g_settings.combatMoveSpeedMultiplier, 0.1f, 5.0f);
        PED::SET_PED_MOVE_RATE_OVERRIDE(fighter.ped, bossMoveRate);
        PED::SET_PED_MAX_MOVE_BLEND_RATIO(fighter.ped, bossMoveRate);
        PED::SET_PED_SHOOT_RATE(fighter.ped, bossShootRate(fighter));
        PED::SET_PED_SEEING_RANGE(fighter.ped, sightRange);
        PED::SET_PED_HEARING_RANGE(fighter.ped, sightRange + 24.0f);
        PED::SET_PED_FIRING_PATTERN(fighter.ped, joaat("FIRING_PATTERN_FULL_AUTO"));
        PED::SET_PED_ACCURACY(fighter.ped, boss.accuracy);
        PED::SET_PED_COMBAT_MOVEMENT(fighter.ped, bossNativeCombatMovement(fighter));
        switch (fighter.boss)
        {
        case kBossMicah:
            PED::SET_PED_COMBAT_RANGE(fighter.ped, 0);
            break;
        case kBossDutch:
            PED::SET_PED_COMBAT_RANGE(fighter.ped, 2);
            break;
        case kBossColm:
            PED::SET_PED_COMBAT_RANGE(fighter.ped, 1);
            break;
        default:
            PED::SET_PED_COMBAT_RANGE(fighter.ped, 1);
            break;
        }

        // Let Rockstar's combat task choose cover after sustained pressure, then
        // return the boss to their usual aggressive movement automatically.
        if (fighter.defensiveCombatUntil > now())
            PED::SET_PED_COMBAT_MOVEMENT(fighter.ped, 1);
    }

    PED::SET_PED_CAN_BE_TARGETTED_BY_PLAYER(
        fighter.ped,
        PLAYER::PLAYER_ID(),
        runtimeRelationToPlayer(fighter.team) != PlayerRelation::Friendly);
    disableAiWeaponSelection(fighter);
    applyExecutionThresholdProtection(fighter, ENTITY::GET_ENTITY_HEALTH(fighter.ped), false);
    applyProtectedHeadshotMultiplierTest(fighter, "static-tuning");
    fighter.lastTune = now();
}

void repairDynamicPedTuning(Fighter& fighter, DWORD t)
{
    if (!exists(fighter.ped))
        return;

    ENTITY::SET_ENTITY_CAN_BE_DAMAGED(fighter.ped, true);
    if (!fighter.cinematicRecoveryActive)
        ENTITY::SET_ENTITY_INVINCIBLE(fighter.ped, false);

    if (fighter.group)
    {
        if (PED::GET_PED_RELATIONSHIP_GROUP_HASH(fighter.ped) != fighter.group)
        {
            PED::SET_PED_RELATIONSHIP_GROUP_DEFAULT_HASH(fighter.ped, fighter.group);
            PED::SET_PED_RELATIONSHIP_GROUP_HASH(fighter.ped, fighter.group);
            applyDamagePermissions(fighter);
            removeFighterBlip(fighter);
        }
    }

    applyDamagePermissions(fighter);
    WEAPON::SET_PED_DROPS_WEAPONS_WHEN_DEAD(fighter.ped, false);
    PED::SET_PED_FLEE_ATTRIBUTES(fighter.ped, 0, false);
    PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(fighter.ped, true);

    const DifficultyTuning& tuning = kDifficulty[static_cast<size_t>(difficultyIndex(fighter.difficulty))];
    float sightRange = combatSightRangeForFighter(fighter);
    float moveRate = std::clamp(tuning.moveRate * g_settings.combatMoveSpeedMultiplier, 0.1f, 5.0f);
    if (fighter.difficulty == Difficulty::Special)
    {
        const SpecialPedDef& special = kSpecialPeds[static_cast<size_t>(fighter.special)];
        moveRate = std::clamp(special.moveRate * g_settings.combatMoveSpeedMultiplier, 0.1f, 5.0f);
        PED::SET_PED_SHOOT_RATE(fighter.ped, special.shootRate);
    }
    else if (fighter.difficulty == Difficulty::Bosses)
    {
        const BossDef& boss = kBosses[static_cast<size_t>(fighter.boss)];
        moveRate = std::clamp(boss.moveRate * g_settings.combatMoveSpeedMultiplier, 0.1f, 5.0f);
        PED::SET_PED_SHOOT_RATE(fighter.ped, bossShootRate(fighter));
        PED::SET_PED_FIRING_PATTERN(fighter.ped, joaat("FIRING_PATTERN_FULL_AUTO"));
        if (fighter.defensiveCombatUntil > t)
            PED::SET_PED_COMBAT_MOVEMENT(fighter.ped, 1);
        else
            PED::SET_PED_COMBAT_MOVEMENT(fighter.ped, bossNativeCombatMovement(fighter));
    }
    else
    {
        PED::SET_PED_SHOOT_RATE(fighter.ped, tuning.shootRate);
    }

    PED::SET_PED_MOVE_RATE_OVERRIDE(fighter.ped, moveRate);
    PED::SET_PED_MAX_MOVE_BLEND_RATIO(fighter.ped, moveRate);
    PED::SET_PED_SEEING_RANGE(fighter.ped, sightRange);
    PED::SET_PED_HEARING_RANGE(fighter.ped, sightRange + (fighter.difficulty == Difficulty::Bosses ? 24.0f : 18.0f));
    if (fighter.hardened)
    {
        PED::SET_PED_CAN_RAGDOLL(fighter.ped, false);
        PED::SET_PED_CAN_RAGDOLL_FROM_PLAYER_IMPACT(fighter.ped, false);
        PED::SET_PED_RAGDOLL_ON_COLLISION(fighter.ped, false, 0);
        PED::_SET_PED_RAGDOLL_BLOCKING_FLAGS(fighter.ped, 0xFFFFFFFF);
    }

    PED::SET_PED_CAN_BE_TARGETTED_BY_PLAYER(
        fighter.ped,
        PLAYER::PLAYER_ID(),
        fighterRelationToPlayer(fighter) != PlayerRelation::Friendly);
    disableAiWeaponSelection(fighter);
    applyExecutionThresholdProtection(fighter, ENTITY::GET_ENTITY_HEALTH(fighter.ped), false);
    fighter.lastTune = t;
}

void applyPedTuning(Fighter& fighter)
{
    applyStaticPedTuning(fighter);
}

void enforceBossRagdollProtection(Fighter& fighter, bool dead)
{
    if (fighter.difficulty != Difficulty::Bosses || !exists(fighter.ped) || dead)
        return;

    PED::SET_PED_CAN_RAGDOLL(fighter.ped, false);
    PED::SET_PED_CAN_RAGDOLL_FROM_PLAYER_IMPACT(fighter.ped, false);
    PED::SET_PED_RAGDOLL_ON_COLLISION(fighter.ped, false, 0);
    PED::_SET_PED_RAGDOLL_BLOCKING_FLAGS(fighter.ped, 0xFFFFFFFF);
    PED::RESET_PED_RAGDOLL_TIMER(fighter.ped);

    if (!fighter.cinematicRecoveryActive &&
        (PED::IS_PED_RAGDOLL(fighter.ped) || PED::IS_PED_RUNNING_RAGDOLL_TASK(fighter.ped)))
    {
        AI::CLEAR_PED_TASKS_IMMEDIATELY(fighter.ped, true, false);
        fighter.lastTask = 0;
        fighter.lastRepositionTask = 0;
        fighter.currentTarget = 0;
        fighter.currentTargetStartedAt = 0;
    }
}

void clearVisibleDamage(Ped ped)
{
    if (!exists(ped))
        return;

    PED::CLEAR_PED_LAST_DAMAGE_BONE(ped);
    ENTITY::CLEAR_ENTITY_LAST_DAMAGE_ENTITY(ped);
    if (ENTITY::GET_ENTITY_HEALTH(ped) > 0)
        PED::CLEAR_PED_BLOOD_DAMAGE(ped);
}

void refillPlayerCores(Ped player)
{
    if (!exists(player))
        return;

    Player playerId = PLAYER::PLAYER_ID();
    for (int core = 0; core < 3; ++core)
        ATTRIBUTE::_0xC6258F41D86676E0(player, core, 100);

    PLAYER::RESTORE_PLAYER_STAMINA(playerId, 100.0f);
    PLAYER::RESTORE_SPECIAL_ABILITY(playerId, -1, false);
    PLAYER::_0x5A498FCA232F71E1(playerId, 100.0f);
    PED::SET_PED_STAMINA(player, 100.0f);
}

void refillPlayerHealthAndCores(Ped player)
{
    if (!exists(player))
        return;

    int maxHealth = std::max(PED::GET_PED_MAX_HEALTH(player), ENTITY::GET_ENTITY_MAX_HEALTH(player, true));
    if (maxHealth <= 0)
        maxHealth = 200;

    ENTITY::SET_ENTITY_HEALTH(player, maxHealth, 0);
    refillPlayerCores(player);
    clearVisibleDamage(player);
}

void refillPlayerHealthAndCoresIfAlive()
{
    Ped player = playerPed();
    if (!exists(player) ||
        PLAYER::IS_PLAYER_DEAD(PLAYER::PLAYER_ID()) ||
        PED::IS_PED_DEAD_OR_DYING(player, true) ||
        PED::IS_PED_FATALLY_INJURED(player))
    {
        return;
    }

    refillPlayerHealthAndCores(player);
    g_runtime.playerVitalsRefillUntil = now() + 2600u;
}

void maintainPlayerVitalsRefill(DWORD t)
{
    if (g_runtime.playerVitalsRefillUntil == 0 || t > g_runtime.playerVitalsRefillUntil)
    {
        g_runtime.playerVitalsRefillUntil = 0;
        return;
    }

    Ped player = playerPed();
    if (!exists(player) ||
        PLAYER::IS_PLAYER_DEAD(PLAYER::PLAYER_ID()) ||
        PED::IS_PED_DEAD_OR_DYING(player, true) ||
        PED::IS_PED_FATALLY_INJURED(player))
    {
        return;
    }

    refillPlayerHealthAndCores(player);
}

void setPlayerSpecialAbilityDisabled(bool disabled);

void restorePlayerDeadEyeControlsThisFrame()
{
    for (int group = 0; group <= 2; ++group)
    {
        CONTROLS::ENABLE_CONTROL_ACTION(group, kInputSpecialAbility, true);
        CONTROLS::ENABLE_CONTROL_ACTION(group, kInputSpecialAbilitySecondary, true);
    }
}

void suppressPlayerDeadEyeControlsThisFrame()
{
    for (int group = 0; group <= 2; ++group)
    {
        CONTROLS::DISABLE_CONTROL_ACTION(group, kInputSpecialAbility, true);
        CONTROLS::DISABLE_CONTROL_ACTION(group, kInputSpecialAbilitySecondary, true);
    }
}

void setPlayerSpecialAbilityDisabled(bool disabled)
{
    invoke<Void>(0xAE637BB8EF017875, PLAYER::PLAYER_ID(), disabled);
}

DWORD bossDodgeDeadEyeDuration()
{
    return std::clamp<DWORD>(g_settings.bossDodgeDeadEyeSuppressMs, kBossDodgeDeadEyeMinMs, kBossDodgeDeadEyeMaxMs);
}

bool playerCanBeBossDodgeDeadEyeBlocked(const Fighter& fighter, Ped target, DWORD t)
{
    if (!g_runtime.battleActive ||
        !g_runtime.playerParticipating ||
        g_runtime.playerSpectating ||
        g_runtime.playerEliminated)
    {
        return false;
    }

    Ped player = playerPed();
    if (!exists(player) ||
        !exists(fighter.ped) ||
        PLAYER::IS_PLAYER_DEAD(PLAYER::PLAYER_ID()) ||
        PED::IS_PED_DEAD_OR_DYING(player, true) ||
        PED::IS_PED_FATALLY_INJURED(player))
    {
        return false;
    }

    Player playerId = PLAYER::PLAYER_ID();
    return target == player ||
        fighter.currentTarget == player ||
        PLAYER::IS_PLAYER_FREE_AIMING_AT_ENTITY(playerId, fighter.ped) ||
        PLAYER::IS_PLAYER_TARGETTING_ENTITY(playerId, fighter.ped, true) ||
        (fighter.lastPlayerDamage != 0 && t - fighter.lastPlayerDamage < 1500u) ||
        ENTITY::HAS_ENTITY_BEEN_DAMAGED_BY_ENTITY(fighter.ped, player, true, true);
}

bool bossMayStartDodgeDeadEyeBlock(const Fighter& fighter, Ped target, DWORD t)
{
    if (fighter.difficulty != Difficulty::Bosses ||
        g_settings.noDeadEyeDuringBattles ||
        !playerCanBeBossDodgeDeadEyeBlocked(fighter, target, t))
    {
        return false;
    }

    if (t < g_runtime.bossDodgeDeadEyeNextAllowedAt)
        return false;

    if (fighter.boss != kBossJohn &&
        fighter.boss != kBossArthur &&
        randomRange(1, 100) > bossDodgeDeadEyeBlockChance(fighter))
    {
        return false;
    }

    return true;
}

void startBossDodgeDeadEyeBlock(Fighter& fighter, Ped target, DWORD t)
{
    if (!fighter.evasionActuallyStarted || !bossMayStartDodgeDeadEyeBlock(fighter, target, t))
        return;

    DWORD duration = bossDodgeDeadEyeDuration();
    fighter.evasionDeadEyeSuppressed = true;
    fighter.evasionDeadEyeBlockStartedAt = t;
    fighter.evasionDeadEyeBlockUntil = t + duration;

    g_runtime.bossDodgeDeadEyeSuppressedUntil = std::max(g_runtime.bossDodgeDeadEyeSuppressedUntil, fighter.evasionDeadEyeBlockUntil);
    g_runtime.bossDodgeDeadEyeSuppressionActive = true;
    g_runtime.bossDodgeDeadEyeLastBoss = fighter.ped;
    g_runtime.bossDodgeDeadEyeNextAllowedAt = fighter.evasionDeadEyeBlockUntil + kBossDodgeDeadEyeGlobalGraceMs;
}

bool startBossMovementDeadEyeBlock(Fighter& fighter, Ped target, DWORD t)
{
    if (!bossMayStartDodgeDeadEyeBlock(fighter, target, t))
        return false;

    DWORD duration = bossDodgeDeadEyeDuration();
    fighter.evasionDeadEyeSuppressed = true;
    fighter.evasionDeadEyeBlockStartedAt = t;
    fighter.evasionDeadEyeBlockUntil = t + duration;

    g_runtime.bossDodgeDeadEyeSuppressedUntil = std::max(g_runtime.bossDodgeDeadEyeSuppressedUntil, fighter.evasionDeadEyeBlockUntil);
    g_runtime.bossDodgeDeadEyeSuppressionActive = true;
    g_runtime.bossDodgeDeadEyeLastBoss = fighter.ped;
    g_runtime.bossDodgeDeadEyeNextAllowedAt = fighter.evasionDeadEyeBlockUntil + kBossDodgeDeadEyeGlobalGraceMs;
    return true;
}

bool updateBossDodgeDeadEyeWindow(Fighter& fighter, DWORD t, DWORD& latestUntil)
{
    if (fighter.evasionDeadEyeBlockUntil == 0)
        return false;

    bool active =
        g_runtime.battleActive &&
        fighter.evasionDeadEyeSuppressed &&
        exists(fighter.ped) &&
        !PED::IS_PED_DEAD_OR_DYING(fighter.ped, true) &&
        !PED::IS_PED_FATALLY_INJURED(fighter.ped) &&
        t < fighter.evasionDeadEyeBlockUntil &&
        playerCanBeBossDodgeDeadEyeBlocked(fighter, fighter.currentTarget, t);

    if (!active)
    {
        fighter.evasionDeadEyeSuppressed = false;
        fighter.evasionDeadEyeBlockStartedAt = 0;
        fighter.evasionDeadEyeBlockUntil = 0;
        return false;
    }

    latestUntil = std::max(latestUntil, fighter.evasionDeadEyeBlockUntil);
    return true;
}

void stopBossDodgeDeadEyeSuppression()
{
    for (Fighter& fighter : g_runtime.fighters)
    {
        fighter.evasionDeadEyeSuppressed = false;
        fighter.evasionDeadEyeBlockStartedAt = 0;
        fighter.evasionDeadEyeBlockUntil = 0;
    }

    bool wasDisabled = g_runtime.bossDodgeDeadEyeSuppressionActive || g_runtime.noDeadEyeModifierActive;
    g_runtime.bossDodgeDeadEyeSuppressionActive = false;
    g_runtime.bossDodgeDeadEyeSuppressedUntil = 0;
    g_runtime.bossDodgeDeadEyeNextAllowedAt = 0;
    g_runtime.bossDodgeDeadEyeLastBoss = 0;
    g_runtime.noDeadEyeModifierActive = g_settings.noDeadEyeDuringBattles && g_runtime.battleActive;
    if (wasDisabled && !g_runtime.noDeadEyeModifierActive)
    {
        restorePlayerDeadEyeControlsThisFrame();
        setPlayerSpecialAbilityDisabled(false);
    }
}

void updatePlayerDeadEyeSuppression(DWORD t)
{
    bool wasDisabled = g_runtime.bossDodgeDeadEyeSuppressionActive || g_runtime.noDeadEyeModifierActive;
    DWORD latestBossBlockUntil = 0;
    bool bossDodgeBlockActive = false;

    for (Fighter& fighter : g_runtime.fighters)
        bossDodgeBlockActive = updateBossDodgeDeadEyeWindow(fighter, t, latestBossBlockUntil) || bossDodgeBlockActive;

    bool noDeadEyeModifierActive = g_settings.noDeadEyeDuringBattles && g_runtime.battleActive;
    bool shouldDisableDeadEye = noDeadEyeModifierActive || bossDodgeBlockActive;

    g_runtime.bossDodgeDeadEyeSuppressionActive = bossDodgeBlockActive;
    g_runtime.bossDodgeDeadEyeSuppressedUntil = latestBossBlockUntil;
    g_runtime.noDeadEyeModifierActive = noDeadEyeModifierActive;

    if (shouldDisableDeadEye)
    {
        suppressPlayerDeadEyeControlsThisFrame();
        setPlayerSpecialAbilityDisabled(true);
        return;
    }

    if (wasDisabled)
    {
        restorePlayerDeadEyeControlsThisFrame();
        setPlayerSpecialAbilityDisabled(false);
    }
}

void clearBattleDeathScreenThisFrame()
{
    UI::HIDE_LOADING_ON_FADE_THIS_FRAME();
    UI::_REMOVE_LOADING_PROMPT();
    SCRIPT::SET_NO_LOADING_SCREEN(true);
    SCRIPT::SHUTDOWN_LOADING_SCREEN();
    GAMEPLAY::IGNORE_NEXT_RESTART(true);
    GRAPHICS::ANIMPOSTFX_STOP_ALL();
    GRAPHICS::CLEAR_TIMECYCLE_MODIFIER();
    CAM::SET_WIDESCREEN_BORDERS(false, 0);
    CAM::DO_SCREEN_FADE_IN(0);
}

void suppressBattleRespawnThisFrame()
{
    if (!g_runtime.playerRespawnOverrideActive && !g_runtime.playerRevivePending)
        return;

    setBattleRespawnOverride(true);
    GAMEPLAY::IGNORE_NEXT_RESTART(true);
    if (g_runtime.playerRevivePending)
    {
        rememberPlayerRevivePosition();
        clearBattleDeathScreenThisFrame();
    }
}

void keepScreenVisibleAfterBattleRevive(DWORD t)
{
    if (!g_runtime.playerEliminated || g_runtime.playerRevivePending)
        return;

    setBattleRespawnOverride(true);
    GAMEPLAY::IGNORE_NEXT_RESTART(true);
    if (g_runtime.playerScreenRepairUntil != 0 && t < g_runtime.playerScreenRepairUntil)
    {
        clearBattleDeathScreenThisFrame();
        return;
    }

    g_runtime.playerScreenRepairUntil = 0;
}

void deletePlayerBattleCorpse()
{
    if (exists(g_runtime.playerBattleCorpse))
    {
        ENTITY::SET_ENTITY_AS_MISSION_ENTITY(g_runtime.playerBattleCorpse, true, true);
        PED::DELETE_PED(&g_runtime.playerBattleCorpse);
    }
    g_runtime.playerBattleCorpse = 0;
}

void preservePlayerBattleCorpse(Ped player)
{
    if (!exists(player) || exists(g_runtime.playerBattleCorpse))
        return;

    Vec3 pos = entityCoords(player);
    float heading = ENTITY::GET_ENTITY_HEADING(player);
    Ped corpse = PED::CLONE_PED(player, heading, false, true);
    if (!exists(corpse))
        return;

    ENTITY::SET_ENTITY_AS_MISSION_ENTITY(corpse, true, true);
    ENTITY::SET_ENTITY_COORDS_NO_OFFSET(corpse, pos.x, pos.y, pos.z, false, false, false);
    ENTITY::SET_ENTITY_HEADING(corpse, heading);
    ENTITY::SET_ENTITY_VISIBLE(corpse, true);
    ENTITY::SET_ENTITY_COLLISION(corpse, true, true);
    PED::SET_PED_CAN_RAGDOLL(corpse, true);
    WEAPON::SET_PED_DROPS_WEAPONS_WHEN_DEAD(corpse, false);
    AI::CLEAR_PED_TASKS_IMMEDIATELY(corpse, true, false);
    PED::SET_PED_TO_RAGDOLL(corpse, -1, -1, 0, true, true, false);
    ENTITY::SET_ENTITY_HEALTH(corpse, 0, 0);
    g_runtime.playerBattleCorpse = corpse;
}

void hidePlayerForBattleSpectator()
{
    Ped player = playerPed();
    if (!exists(player))
        return;

    Player playerId = PLAYER::PLAYER_ID();
    if (!g_runtime.playerHiddenForSpectator)
    {
        g_runtime.spectatorReturnPos = entityCoords(player);
        g_runtime.spectatorReturnHeading = ENTITY::GET_ENTITY_HEADING(player);
        g_runtime.spectatorReturnPosValid = true;
    }
    ENTITY::FREEZE_ENTITY_POSITION(player, true);
    ENTITY::SET_ENTITY_COLLISION(player, false, false);
    ENTITY::SET_ENTITY_VISIBLE(player, false);
    ENTITY::SET_ENTITY_ALPHA(player, 0, false);
    NETWORK::SET_LOCAL_PLAYER_INVISIBLE_LOCALLY(true);
    NETWORK::SET_PLAYER_INVISIBLE_LOCALLY(playerId, true);
    NETWORK::SET_PLAYER_VISIBLE_LOCALLY(playerId, false);
    PLAYER::SET_PLAYER_INVINCIBLE(playerId, true);
    g_runtime.playerHiddenForSpectator = true;
}

void keepPlayerNearSpectatorTarget(const Fighter& target, DWORD t)
{
    Ped player = playerPed();
    if (!exists(player) || !exists(target.ped))
        return;

    hidePlayerForBattleSpectator();
    Vec3 targetPos = entityCoords(target.ped);
    Vec3 followPos = fromNative(ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(target.ped, 0.0f, -2.8f, 0.08f));
    float distSq = distanceSquared(entityCoords(player), followPos);
    if (g_runtime.lastSpectatorPlayerFollowAt == 0 ||
        t - g_runtime.lastSpectatorPlayerFollowAt >= 250u ||
        distSq > 16.0f)
    {
        STREAMING::REQUEST_COLLISION_AT_COORD(targetPos.x, targetPos.y, targetPos.z);
        STREAMING::REQUEST_COLLISION_AT_COORD(followPos.x, followPos.y, followPos.z);
        PATHFIND::ADD_NAVMESH_REQUIRED_REGION(targetPos.x, targetPos.y, 24.0f);
        ENTITY::FREEZE_ENTITY_POSITION(player, false);
        ENTITY::SET_ENTITY_COORDS_NO_OFFSET(player, followPos.x, followPos.y, followPos.z, false, false, false);
        ENTITY::SET_ENTITY_HEADING(player, ENTITY::GET_ENTITY_HEADING(target.ped));
        AI::CLEAR_PED_TASKS_IMMEDIATELY(player, true, false);
        ENTITY::FREEZE_ENTITY_POSITION(player, true);
        g_runtime.lastSpectatorPlayerFollowAt = t;
    }

    ENTITY::SET_ENTITY_COLLISION(player, false, false);
    ENTITY::SET_ENTITY_VISIBLE(player, false);
    ENTITY::SET_ENTITY_ALPHA(player, 0, false);
    PLAYER::SET_PLAYER_INVINCIBLE(PLAYER::PLAYER_ID(), true);
}

DWORD playerBattleReviveDelay()
{
    if (!g_runtime.deathmatch &&
        g_settings.forcePlayerSpectator &&
        g_runtime.playerWasParticipant &&
        g_runtime.playerEliminated)
    {
        return kPlayerSpectatorReviveDelayMs;
    }

    return kPlayerBattleReviveDelayMs;
}

void restorePlayerAfterBattleSpectator()
{
    if (!g_runtime.playerHiddenForSpectator)
        return;

    Ped player = playerPed();
    if (exists(player))
    {
        Player playerId = PLAYER::PLAYER_ID();
        if (g_runtime.lastSpectatorPlayerFollowAt != 0)
        {
            Vec3 pos = entityCoords(player);
            snapToGround(pos);
            STREAMING::REQUEST_COLLISION_AT_COORD(pos.x, pos.y, pos.z);
            ENTITY::SET_ENTITY_COORDS_NO_OFFSET(player, pos.x, pos.y, pos.z, false, false, false);
        }
        else if (g_runtime.spectatorReturnPosValid)
        {
            Vec3 pos = g_runtime.spectatorReturnPos;
            snapToGround(pos);
            STREAMING::REQUEST_COLLISION_AT_COORD(pos.x, pos.y, pos.z);
            ENTITY::SET_ENTITY_COORDS_NO_OFFSET(player, pos.x, pos.y, pos.z, false, false, false);
            ENTITY::SET_ENTITY_HEADING(player, g_runtime.spectatorReturnHeading);
        }
        NETWORK::SET_LOCAL_PLAYER_INVISIBLE_LOCALLY(false);
        NETWORK::SET_PLAYER_INVISIBLE_LOCALLY(playerId, false);
        NETWORK::SET_PLAYER_VISIBLE_LOCALLY(playerId, true);
        ENTITY::FREEZE_ENTITY_POSITION(player, false);
        ENTITY::SET_ENTITY_COLLISION(player, true, true);
        ENTITY::SET_ENTITY_VISIBLE(player, true);
        ENTITY::RESET_ENTITY_ALPHA(player);
    }
    g_runtime.playerHiddenForSpectator = false;
    g_runtime.spectatorReturnPosValid = false;
    g_runtime.lastSpectatorPlayerFollowAt = 0;
}

void schedulePlayerBattleRevive(DWORD t)
{
    if (g_runtime.playerRevivePending)
        return;

    rememberPlayerRevivePosition();

    DWORD reviveDelay = playerBattleReviveDelay();
    g_runtime.playerRevivePending = true;
    g_runtime.playerReviveAt = t + reviveDelay;
    g_runtime.playerScreenRepairUntil = t + reviveDelay + kPlayerScreenRepairAfterReviveMs;
    setBattleRespawnOverride(true);
    GAMEPLAY::IGNORE_NEXT_RESTART(true);
    clearBattleDeathScreenThisFrame();
}

void revivePlayerAtBattleSpot(DWORD t)
{
    if (!g_runtime.playerRevivePending || t < g_runtime.playerReviveAt)
        return;

    Ped player = playerPed();
    if (!exists(player))
        return;

    Vec3 pos = g_runtime.playerSafePosValid ? g_runtime.playerLastSafePos : entityCoords(player);
    snapToGround(pos);
    float heading = g_runtime.playerLastSafeHeading;

    if (!g_runtime.deathmatch &&
        g_settings.forcePlayerSpectator &&
        g_runtime.playerWasParticipant &&
        g_runtime.playerEliminated)
    {
        preservePlayerBattleCorpse(player);
    }

    NETWORK::NETWORK_RESURRECT_LOCAL_PLAYER(pos.x, pos.y, pos.z, heading, true, false, 0, false);
    player = playerPed();
    if (!exists(player))
        return;

    PED::RESURRECT_PED(player);
    PED::REVIVE_INJURED_PED(player);
    ENTITY::SET_ENTITY_COORDS_NO_OFFSET(player, pos.x, pos.y, pos.z, false, false, false);
    ENTITY::SET_ENTITY_HEADING(player, heading);
    AI::CLEAR_PED_TASKS_IMMEDIATELY(player, true, false);
    PED::RESET_PED_RAGDOLL_TIMER(player);

    int maxHealth = std::max(PED::GET_PED_MAX_HEALTH(player), ENTITY::GET_ENTITY_MAX_HEALTH(player, true));
    if (maxHealth <= 0)
        maxHealth = 200;
    ENTITY::SET_ENTITY_HEALTH(player, maxHealth, 0);
    refillPlayerCores(player);
    clearVisibleDamage(player);
    resetPlayerDamageAttribution();

    PLAYER::SET_PLAYER_CONTROL(PLAYER::PLAYER_ID(), true, 0, false);
    PLAYER::SET_PLAYER_INVINCIBLE(PLAYER::PLAYER_ID(), false);
    g_runtime.playerScreenRepairUntil = t + kPlayerScreenRepairAfterReviveMs;
    clearBattleDeathScreenThisFrame();

    g_runtime.playerRevivePending = false;
    g_runtime.playerSafePosValid = true;
    g_runtime.playerLastSafePos = entityCoords(player);
    g_runtime.playerLastSafeHeading = ENTITY::GET_ENTITY_HEADING(player);
    if (g_runtime.deathmatch && g_runtime.playerWasParticipant)
    {
        g_runtime.playerEliminated = false;
        g_runtime.playerParticipating = true;
        markRelationshipsDirty();
        updateRelationshipsIfNeeded(t);
        for (Fighter& fighter : g_runtime.fighters)
        {
            if (exists(fighter.ped))
                applyDamagePermissions(fighter);
            removeFighterBlip(fighter);
            ensureFighterBlip(fighter);
        }
        setStatus("You are back in the match", 4500);
    }
    else
    {
        setStatus("You are back at the battle - spectator mode", 7000);
        if (g_settings.forcePlayerSpectator)
        {
            hidePlayerForBattleSpectator();
            selectSpectatorCameraTarget(1);
        }
    }
}

int recoveryHealthForBoss(const Fighter& fighter)
{
    if (fighter.lastHealth > 0)
        return std::clamp(fighter.lastHealth, 1, fighter.maxHealth);
    return std::clamp(ENTITY::GET_ENTITY_HEALTH(fighter.ped), 1, fighter.maxHealth);
}

int blockedExecutionRecoveryHealthForBoss(const Fighter& fighter)
{
    int baseHealth = recoveryHealthForBoss(fighter);
    return std::clamp(baseHealth - g_settings.bossBlockedExecutionDamage, 1, fighter.maxHealth);
}

int executionHealthThreshold(const Fighter& fighter)
{
    if (fighter.difficulty == Difficulty::Bosses)
        return g_settings.bossExecutionHealthThreshold;
    if (fighter.difficulty == Difficulty::Extreme)
        return g_settings.extremeExecutionHealthThreshold;
    if (fighter.difficulty == Difficulty::Special)
        return g_settings.extremeExecutionHealthThreshold;
    return 0;
}

bool underExecutionHealthThreshold(const Fighter& fighter, int health, bool dead)
{
    int threshold = executionHealthThreshold(fighter);
    if (threshold <= 0)
        return false;

    return (dead && fighter.lastHealth > 0 && fighter.lastHealth <= threshold) ||
        (!dead && health > 0 && health <= threshold);
}

bool restorePlayerFriendlyFire(Fighter& fighter, int& health, bool& dead, DWORD t)
{
    if (freeForAllActive())
        return false;

    if (fighter.team < 0 ||
        fighter.team >= kTeamCount ||
        runtimeRelationToPlayer(fighter.team) != PlayerRelation::Friendly)
    {
        return false;
    }

    if (!ENTITY::HAS_ENTITY_BEEN_DAMAGED_BY_ENTITY(fighter.ped, playerPed(), true, true))
        return false;

    if (!dead && health >= fighter.lastHealth)
    {
        ENTITY::CLEAR_ENTITY_LAST_DAMAGE_ENTITY(fighter.ped);
        PED::CLEAR_PED_LAST_DAMAGE_BONE(fighter.ped);
        return false;
    }

    if (dead)
    {
        PED::RESURRECT_PED(fighter.ped);
        PED::REVIVE_INJURED_PED(fighter.ped);
        dead = false;
    }

    int restored = std::clamp(fighter.lastHealth > 0 ? fighter.lastHealth : fighter.maxHealth, 1, fighter.maxHealth);
    ENTITY::SET_ENTITY_HEALTH(fighter.ped, restored, 0);
    health = restored;
    clearVisibleDamage(fighter.ped);
    if (PED::IS_PED_IN_COMBAT(fighter.ped, playerPed()) ||
        PED::GET_MELEE_TARGET_FOR_PED(fighter.ped) == playerPed())
    {
        AI::CLEAR_PED_TASKS(fighter.ped, true, false);
        fighter.currentTarget = 0;
        fighter.currentTargetStartedAt = 0;
        fighter.lastTask = 0;
    }
    fighter.lastDamage = t;
    fighter.lastHealth = restored;
    return true;
}

bool isEliteCorpseDifficulty(Difficulty difficulty)
{
    return difficulty == Difficulty::Bosses || difficulty == Difficulty::Special;
}

DWORD corpseMinimumLifetime(Difficulty difficulty)
{
    return isEliteCorpseDifficulty(difficulty) ?
        g_settings.eliteCorpseLifetimeMs :
        g_settings.normalCorpseLifetimeMs;
}

Object trackedWeaponObjectForPed(Ped ped)
{
    if (!exists(ped) || !g_settings.cleanTrackedDroppedWeapons)
        return 0;

    Entity weaponEntity = WEAPON::GET_CURRENT_PED_WEAPON_ENTITY_INDEX(ped, 0);
    if (!exists(weaponEntity))
        return 0;

    Object object = ENTITY::GET_OBJECT_INDEX_FROM_ENTITY_INDEX(weaponEntity);
    return exists(object) ? object : 0;
}

void initialiseFighterCorpseState(Fighter& fighter, DWORD t)
{
    if (fighter.corpseCleanupQueued || fighter.corpseDeleted || !exists(fighter.ped))
        return;

    fighter.diedAt = t;
    fighter.deathPosition = entityCoords(fighter.ped);
    fighter.corpseCleanupEligibleAt = t + corpseMinimumLifetime(fighter.difficulty);
    fighter.lastCorpseCleanupCheck = 0;
    fighter.corpseCleanupQueued = true;
    fighter.corpseDeleted = false;
    fighter.droppedWeaponObject = trackedWeaponObjectForPed(fighter.ped);
    fighter.pendingCombatWeapon = 0;
    fighter.pendingWeaponTarget = 0;
    fighter.pendingWeaponSince = 0;
    fighter.weaponPending = 0;
    fighter.temporaryWeaponOverride = 0;
    fighter.temporaryWeaponOverrideUntil = 0;
    fighter.rangeWeaponCandidate = 0;
    fighter.rangeWeaponCandidateTarget = 0;
    fighter.rangeWeaponCandidateSince = 0;
    resetWeaponController(fighter);
    resetScriptedActionState(fighter, true);
}

void clearReferencesToDeletedPed(Ped ped)
{
    if (!ped)
        return;

    DWORD t = now();
    for (Fighter& fighter : g_runtime.fighters)
    {
        bool cleared = false;
        if (fighter.currentTarget == ped)
        {
            fighter.currentTarget = 0;
            fighter.currentTargetStartedAt = 0;
            fighter.lastTask = 0;
            cleared = true;
        }
        if (fighter.projectileTarget == ped)
        {
            fighter.projectileTarget = 0;
            cleared = true;
        }
        if (fighter.evasionThreat == ped)
        {
            fighter.evasionThreat = 0;
            cleared = true;
        }
        if (fighter.evasionAimTarget == ped)
        {
            fighter.evasionAimTarget = 0;
            cleared = true;
        }
        if (fighter.evasionFiringTarget == ped)
        {
            fighter.evasionFiringTarget = 0;
            cleared = true;
        }
        if (fighter.idleWatchdogTarget == ped)
        {
            fighter.idleWatchdogTarget = 0;
            cleared = true;
        }
        if (fighter.pendingWeaponTarget == ped)
        {
            fighter.pendingWeaponTarget = 0;
            fighter.pendingCombatWeapon = 0;
            fighter.pendingWeaponSince = 0;
            cleared = true;
        }
        if (fighter.rangeWeaponCandidateTarget == ped)
        {
            fighter.rangeWeaponCandidate = 0;
            fighter.rangeWeaponCandidateTarget = 0;
            fighter.rangeWeaponCandidateSince = 0;
            cleared = true;
        }
        if (cleared)
        {
            if (deathmatchActive())
            {
                DWORD stagger = static_cast<DWORD>(std::max(0, fighter.spawnIndex) % 12) * 35u;
                fighter.nextCombatUpdateAt = std::max(fighter.nextCombatUpdateAt, t + stagger);
            }
            ++g_runtime.staleTargetReferencesCleared;
        }
    }

    if (g_runtime.playerKillerPed == ped)
        g_runtime.playerKillerPed = 0;

    if (g_runtime.spectatorTargetIndex >= 0 &&
        g_runtime.spectatorTargetIndex < static_cast<int>(g_runtime.fighters.size()) &&
        g_runtime.fighters[static_cast<size_t>(g_runtime.spectatorTargetIndex)].ped == ped)
    {
        g_runtime.spectatorTargetIndex = -1;
    }
    if (g_runtime.preferredSpectatorTargetIndex >= 0 &&
        g_runtime.preferredSpectatorTargetIndex < static_cast<int>(g_runtime.fighters.size()) &&
        g_runtime.fighters[static_cast<size_t>(g_runtime.preferredSpectatorTargetIndex)].ped == ped)
    {
        g_runtime.preferredSpectatorTargetIndex = -1;
    }
    if (g_runtime.spectatorCameraLastTargetIndex >= 0 &&
        g_runtime.spectatorCameraLastTargetIndex < static_cast<int>(g_runtime.fighters.size()) &&
        g_runtime.fighters[static_cast<size_t>(g_runtime.spectatorCameraLastTargetIndex)].ped == ped)
    {
        g_runtime.spectatorCameraLastTargetIndex = -1;
    }
}

bool safeToCleanupCorpse(Ped ped, const Vec3& position, DWORD diedAt, DWORD eligibleAt, bool elite, DWORD t, int corpseCount)
{
    if (!exists(ped) || t < eligibleAt)
        return false;
    if (ENTITY::IS_ENTITY_ATTACHED(ped) ||
        ENTITY::IS_ENTITY_ATTACHED_TO_ANY_OBJECT(ped) ||
        ENTITY::IS_ENTITY_ATTACHED_TO_ANY_PED(ped) ||
        ENTITY::IS_ENTITY_ATTACHED_TO_ANY_VEHICLE(ped))
    {
        return false;
    }

    Player playerId = PLAYER::PLAYER_ID();
    if (PLAYER::IS_PLAYER_FREE_AIMING_AT_ENTITY(playerId, ped) ||
        PLAYER::IS_PLAYER_TARGETTING_ENTITY(playerId, ped, true))
    {
        return false;
    }

    Ped player = playerPed();
    Vec3 playerPos = exists(player) ? entityCoords(player) : g_runtime.battleCenter;
    float minDistance = g_settings.corpseCleanupMinPlayerDistance;
    float distSq = distanceSquared(playerPos, position);
    bool nearPlayer = distSq < minDistance * minDistance;
    bool onScreen = ENTITY::IS_ENTITY_ON_SCREEN(ped) != 0;
    DWORD age = t - diedAt;
    bool maxAge = age >= g_settings.maximumCorpseLifetimeMs;
    bool overPreferred = corpseCount > g_settings.preferredMaximumCorpses;
    bool overHard = corpseCount > g_settings.hardMaximumCorpses;

    if (nearPlayer)
        return false;
    if (onScreen && !maxAge)
        return false;
    if (elite && !maxAge && !overHard)
        return false;
    if (overHard)
        return !onScreen || distSq > (minDistance * 1.75f) * (minDistance * 1.75f);
    if (overPreferred)
        return !onScreen;
    if (maxAge)
        return !onScreen || distSq > (minDistance * 2.0f) * (minDistance * 2.0f);
    return !onScreen;
}

void deleteTrackedWeaponObject(Object& object)
{
    if (!object)
        return;
    if (exists(object))
    {
        ENTITY::SET_ENTITY_AS_MISSION_ENTITY(object, true, true);
        if (ENTITY::IS_ENTITY_ATTACHED(object))
            ENTITY::DETACH_ENTITY(object, true, true);
        OBJECT::DELETE_OBJECT(&object);
        ++g_runtime.trackedDroppedWeaponsDeleted;
    }
    object = 0;
}

bool safelyDeleteBattleCorpse(Ped& corpse, Object& droppedWeaponObject)
{
    if (!corpse)
        return true;
    if (!exists(corpse))
    {
        corpse = 0;
        droppedWeaponObject = 0;
        return true;
    }

    clearReferencesToDeletedPed(corpse);
    deleteTrackedWeaponObject(droppedWeaponObject);
    ENTITY::SET_ENTITY_AS_MISSION_ENTITY(corpse, true, true);
    if (ENTITY::IS_ENTITY_ATTACHED(corpse))
        ENTITY::DETACH_ENTITY(corpse, true, true);
    AI::CLEAR_PED_TASKS(corpse, true, false);
    PED::DELETE_PED(&corpse);
    if (exists(corpse))
        return false;

    corpse = 0;
    return true;
}

DWORD deathmatchRespawnStagger(const Fighter& fighter)
{
    return static_cast<DWORD>(std::max(0, fighter.spawnIndex) % 8) * 40u;
}

void beginDeathmatchRespawnBookkeeping(Fighter& fighter, DWORD t)
{
    fighter.respawnState = DeathmatchRespawnState::WaitingForCorpseDeletion;
    fighter.pendingRespawn = false;
    fighter.corpseDeleteAt = t + (g_settings.immediateDeathmatchNpcCorpseCleanup ? g_settings.deathmatchCorpseVisibleMs : 0u);
    fighter.respawnReadyAt = t + g_settings.npcDeathmatchRespawnDelayMs + deathmatchRespawnStagger(fighter);
    fighter.respawnAt = fighter.respawnReadyAt;
    fighter.respawnAttempts = 0;
    fighter.droppedWeaponObject = trackedWeaponObjectForPed(fighter.ped);
}

int pendingDeathmatchCorpseDeletionCount()
{
    int count = 0;
    for (const Fighter& fighter : g_runtime.fighters)
    {
        if (fighter.respawnState == DeathmatchRespawnState::WaitingForCorpseDeletion &&
            exists(fighter.ped))
        {
            ++count;
        }
    }
    return count;
}

int queuedDeathmatchRespawnCount()
{
    if (g_runtime.deathmatchRespawnQueueCursor >= g_runtime.deathmatchRespawnQueue.size())
        return 0;
    return static_cast<int>(g_runtime.deathmatchRespawnQueue.size() - g_runtime.deathmatchRespawnQueueCursor);
}

int pendingDeathmatchRespawnCount()
{
    int count = 0;
    for (const Fighter& fighter : g_runtime.fighters)
    {
        if (fighter.pendingRespawn &&
            fighter.respawnState == DeathmatchRespawnState::WaitingForRespawn)
        {
            ++count;
        }
    }
    return count;
}

int trackedDroppedWeaponObjectCount()
{
    int count = 0;
    for (const Fighter& fighter : g_runtime.fighters)
    {
        if (exists(fighter.droppedWeaponObject))
            ++count;
    }

    for (const BattleCorpse& corpse : g_runtime.battleCorpses)
    {
        if (exists(corpse.droppedWeaponObject))
            ++count;
    }
    return count;
}

bool deathmatchRespawnPressureHigh()
{
    if (!deathmatchActive())
        return false;

    int pendingCorpses = pendingDeathmatchCorpseDeletionCount();
    if (pendingCorpses > std::max(2, g_settings.deathmatchMaximumRespawnsPerFrame * 4))
        return true;

    if (g_settings.preventPersistentDroppedWeapons)
    {
        int trackedWeapons = trackedDroppedWeaponObjectCount();
        int fighterCount = std::max(1, static_cast<int>(g_runtime.fighters.size()));
        return trackedWeapons > std::max(8, fighterCount / 3);
    }
    return false;
}

bool deleteDeathmatchPedEntity(Fighter& fighter)
{
    if (!fighter.ped)
        return true;

    if (!exists(fighter.ped))
    {
        fighter.ped = 0;
        if (g_settings.preventPersistentDroppedWeapons)
            deleteTrackedWeaponObject(fighter.droppedWeaponObject);
        return true;
    }

    clearReferencesToDeletedPed(fighter.ped);
    removeFighterBlip(fighter);
    if (!fighter.droppedWeaponObject)
        fighter.droppedWeaponObject = trackedWeaponObjectForPed(fighter.ped);
    if (g_settings.preventPersistentDroppedWeapons)
        deleteTrackedWeaponObject(fighter.droppedWeaponObject);

    ENTITY::SET_ENTITY_AS_MISSION_ENTITY(fighter.ped, true, true);
    if (ENTITY::IS_ENTITY_ATTACHED(fighter.ped))
        ENTITY::DETACH_ENTITY(fighter.ped, true, true);
    if (PED::IS_PED_IN_GROUP(fighter.ped))
        PED::REMOVE_PED_FROM_GROUP(fighter.ped);
    AI::CLEAR_PED_TASKS(fighter.ped, true, false);

    Ped deadPed = fighter.ped;
    PED::DELETE_PED(&deadPed);
    if (exists(deadPed))
    {
        ++g_runtime.corpseDeletionRetries;
        return false;
    }

    fighter.ped = 0;
    fighter.blip = 0;
    fighter.currentTarget = 0;
    fighter.pendingWeaponTarget = 0;
    fighter.rangeWeaponCandidateTarget = 0;
    fighter.projectileTarget = 0;
    fighter.evasionThreat = 0;
    fighter.evasionAimTarget = 0;
    fighter.evasionFiringTarget = 0;
    fighter.corpseCleanupQueued = false;
    fighter.corpseDeleted = true;
    ++g_runtime.corpsesRemoved;
    return true;
}

void recordFighterDeath(Fighter& victim)
{
    if (victim.deathRecorded)
        return;

    int victimIndex = -1;
    for (int i = 0; i < static_cast<int>(g_runtime.fighters.size()); ++i)
    {
        if (&g_runtime.fighters[static_cast<size_t>(i)] == &victim)
        {
            victimIndex = i;
            break;
        }
    }

    victim.deathRecorded = true;
    DWORD t = now();
    if (g_runtime.deathmatch)
    {
        ++victim.deaths;
    }
    else
    {
        int aliveAfterDeath = aliveFighterCount() + (playerAliveInBattle() ? 1 : 0);
        victim.finishPosition = std::max(1, aliveAfterDeath + 1);
    }

    Entity source = PED::GET_PED_SOURCE_OF_DEATH(victim.ped);
    Ped player = PLAYER::PLAYER_PED_ID();
    bool killAttributed = false;
    if (source && player && source == player)
    {
        ++g_runtime.playerKills;
        if (g_runtime.spectatorCameraActive && g_runtime.spectatorTargetIndex == victimIndex)
            g_runtime.spectatorTargetIndex = -1;
        killAttributed = true;
    }

    for (int i = 0; !killAttributed && i < static_cast<int>(g_runtime.fighters.size()); ++i)
    {
        Fighter& killer = g_runtime.fighters[static_cast<size_t>(i)];
        if (killer.ped == victim.ped)
            continue;

        if (source && killer.ped == source)
        {
            ++killer.kills;
            if (g_runtime.spectatorCameraActive &&
                g_runtime.spectatorTargetIndex == victimIndex &&
                exists(killer.ped) &&
                !PED::IS_PED_DEAD_OR_DYING(killer.ped, true) &&
                !PED::IS_PED_FATALLY_INJURED(killer.ped))
            {
                g_runtime.spectatorTargetIndex = i;
            }
            killAttributed = true;
        }
    }

    if (!killAttributed && g_runtime.spectatorCameraActive && g_runtime.spectatorTargetIndex == victimIndex)
        g_runtime.spectatorTargetIndex = -1;

    if (g_runtime.deathmatch)
        beginDeathmatchRespawnBookkeeping(victim, t);
    else
        initialiseFighterCorpseState(victim, t);
}

struct DistantSimulationCandidate
{
    int index = -1;
    int weight = 0;
};

bool sameSimulatedBattleSide(const Fighter& a, const Fighter& b)
{
    if (freeForAllActive())
        return a.group && b.group && a.group == b.group;

    return a.team == b.team;
}

int distantSimulationNpcSideCount()
{
    if (g_runtime.freeForAll)
    {
        std::vector<Hash> groups;
        groups.reserve(g_runtime.fighters.size());
        for (const Fighter& fighter : g_runtime.fighters)
        {
            if (!isAlive(fighter) || !fighter.group)
                continue;
            if (std::find(groups.begin(), groups.end(), fighter.group) == groups.end())
                groups.push_back(fighter.group);
        }
        return static_cast<int>(groups.size());
    }

    std::array<bool, kTeamCount> teams{};
    for (const Fighter& fighter : g_runtime.fighters)
    {
        if (isAlive(fighter) && fighter.team >= 0 && fighter.team < kTeamCount)
            teams[static_cast<size_t>(fighter.team)] = true;
    }

    int count = 0;
    for (bool active : teams)
    {
        if (active)
            ++count;
    }
    return count;
}

bool distantBattleSimulationCanKeepBattleAlive()
{
    return g_settings.enableDistantBattleSimulation &&
        g_runtime.battleActive &&
        !g_runtime.resultAnnounced &&
        !g_runtime.startCountdownActive &&
        distantSimulationNpcSideCount() > 1;
}

Vec3 distantSimulationReferencePosition()
{
    if (g_runtime.spectatorCameraActive &&
        g_runtime.spectatorTargetIndex >= 0 &&
        g_runtime.spectatorTargetIndex < static_cast<int>(g_runtime.fighters.size()))
    {
        const Fighter& target = g_runtime.fighters[static_cast<size_t>(g_runtime.spectatorTargetIndex)];
        if (isAlive(target))
            return entityCoords(target.ped);
    }

    Ped player = playerPed();
    if (exists(player))
        return entityCoords(player);

    return g_runtime.battleCenter;
}

int distantSimulationVictimBaseWeight(const Fighter& fighter)
{
    switch (fighter.difficulty)
    {
    case Difficulty::Easy:
        return 1050;
    case Difficulty::Medium:
        return 70;
    case Difficulty::Hard:
        return 34;
    case Difficulty::Extreme:
        return 9;
    case Difficulty::Special:
        return 18;
    case Difficulty::Bosses:
        return 2;
    }
    return 30;
}

int distantSimulationKillerBaseWeight(const Fighter& fighter)
{
    switch (fighter.difficulty)
    {
    case Difficulty::Easy:
        return 20;
    case Difficulty::Medium:
        return 120;
    case Difficulty::Hard:
        return 420;
    case Difficulty::Extreme:
        return 1300;
    case Difficulty::Special:
        return 3600;
    case Difficulty::Bosses:
        return 12500;
    }
    return 110;
}

int chooseWeightedDistantCandidate(const std::vector<DistantSimulationCandidate>& candidates)
{
    int total = 0;
    for (const DistantSimulationCandidate& candidate : candidates)
        total += std::max(0, candidate.weight);

    if (total <= 0)
        return -1;

    int roll = randomRange(1, total);
    int cursor = 0;
    for (const DistantSimulationCandidate& candidate : candidates)
    {
        cursor += std::max(0, candidate.weight);
        if (roll <= cursor)
            return candidate.index;
    }

    return candidates.empty() ? -1 : candidates.back().index;
}

bool distantSimulationFighterOutOfRange(const Fighter& fighter, Vec3 reference, float distanceLimit)
{
    float limitSq = distanceLimit * distanceLimit;
    if (!isAlive(fighter))
        return false;
    if (ENTITY::IS_ENTITY_ON_SCREEN(fighter.ped))
        return false;
    return distanceSquared(entityCoords(fighter.ped), reference) >= limitSq;
}

std::vector<int> distantSimulationOutOfRangeIndices(Vec3 reference, float distanceLimit)
{
    std::vector<int> indices;
    indices.reserve(g_runtime.fighters.size());
    for (int i = 0; i < static_cast<int>(g_runtime.fighters.size()); ++i)
    {
        const Fighter& fighter = g_runtime.fighters[static_cast<size_t>(i)];
        if (distantSimulationFighterOutOfRange(fighter, reference, distanceLimit))
            indices.push_back(i);
    }
    return indices;
}

bool fighterHasSimulatedEnemyInSet(int fighterIndex, const std::vector<int>& indices)
{
    if (fighterIndex < 0 || fighterIndex >= static_cast<int>(g_runtime.fighters.size()))
        return false;

    const Fighter& fighter = g_runtime.fighters[static_cast<size_t>(fighterIndex)];
    if (!isAlive(fighter))
        return false;

    for (int otherIndex : indices)
    {
        if (otherIndex == fighterIndex ||
            otherIndex < 0 ||
            otherIndex >= static_cast<int>(g_runtime.fighters.size()))
        {
            continue;
        }

        const Fighter& other = g_runtime.fighters[static_cast<size_t>(otherIndex)];
        if (isAlive(other) && !sameSimulatedBattleSide(fighter, other))
            return true;
    }
    return false;
}

Hash distantSimulationSideKey(const Fighter& fighter)
{
    if (g_runtime.freeForAll)
        return fighter.group ? fighter.group : static_cast<Hash>(fighter.ped);

    return static_cast<Hash>(fighter.team + 1);
}

int distantSimulationEligibleSideCount(const std::vector<int>& indices)
{
    std::vector<Hash> sides;
    sides.reserve(indices.size());
    for (int index : indices)
    {
        if (index < 0 || index >= static_cast<int>(g_runtime.fighters.size()))
            continue;
        if (!fighterHasSimulatedEnemyInSet(index, indices))
            continue;

        Hash side = distantSimulationSideKey(g_runtime.fighters[static_cast<size_t>(index)]);
        if (side && std::find(sides.begin(), sides.end(), side) == sides.end())
            sides.push_back(side);
    }

    return static_cast<int>(sides.size());
}

bool hasDistantSimulationVictimCandidate(const std::vector<int>& indices)
{
    for (int index : indices)
    {
        if (fighterHasSimulatedEnemyInSet(index, indices))
            return true;
    }
    return false;
}

int chooseDistantSimulationVictimIndex(const std::vector<int>& indices, Vec3 reference, float distanceLimit)
{
    std::vector<DistantSimulationCandidate> candidates;
    candidates.reserve(indices.size());

    for (int i : indices)
    {
        if (i < 0 || i >= static_cast<int>(g_runtime.fighters.size()))
            continue;

        const Fighter& fighter = g_runtime.fighters[static_cast<size_t>(i)];
        if (!isAlive(fighter) || !fighterHasSimulatedEnemyInSet(i, indices))
            continue;

        float distSq = distanceSquared(entityCoords(fighter.ped), reference);
        float dist = std::sqrt(distSq);
        float distanceBonus = 1.0f + std::clamp((dist - distanceLimit) / std::max(1.0f, distanceLimit), 0.0f, 2.0f) * 0.45f;
        int weight = std::max(1, static_cast<int>(static_cast<float>(distantSimulationVictimBaseWeight(fighter)) * distanceBonus));
        candidates.push_back({ i, weight });
    }

    return chooseWeightedDistantCandidate(candidates);
}

int chooseDistantSimulationKillerIndex(int victimIndex, const std::vector<int>& indices)
{
    if (victimIndex < 0 || victimIndex >= static_cast<int>(g_runtime.fighters.size()))
        return -1;

    const Fighter& victim = g_runtime.fighters[static_cast<size_t>(victimIndex)];
    std::vector<DistantSimulationCandidate> candidates;
    candidates.reserve(indices.size());

    for (int i : indices)
    {
        if (i == victimIndex)
            continue;
        if (i < 0 || i >= static_cast<int>(g_runtime.fighters.size()))
            continue;

        const Fighter& fighter = g_runtime.fighters[static_cast<size_t>(i)];
        if (!isAlive(fighter) || sameSimulatedBattleSide(fighter, victim))
            continue;

        int weight = distantSimulationKillerBaseWeight(fighter);
        int health = exists(fighter.ped) ? ENTITY::GET_ENTITY_HEALTH(fighter.ped) : fighter.lastHealth;
        if (fighter.maxHealth > 0 && health > 0)
        {
            float ratio = static_cast<float>(health) / static_cast<float>(fighter.maxHealth);
            if (ratio > 0.75f)
                weight += weight / 6;
            else if (ratio < 0.25f)
                weight = std::max(1, (weight * 2) / 3);
        }
        candidates.push_back({ i, weight });
    }

    return chooseWeightedDistantCandidate(candidates);
}

DWORD distantSimulationTickForAliveCount(int alive)
{
    DWORD base = std::max<DWORD>(500u, g_settings.distantBattleSimulationTickMs);
    float multiplier = 1.0f;
    if (alive >= 90)
        multiplier = 0.26f;
    else if (alive >= 65)
        multiplier = 0.34f;
    else if (alive >= 45)
        multiplier = 0.48f;
    else if (alive >= 28)
        multiplier = 0.72f;
    else if (alive >= 18)
        multiplier = 1.08f;
    else if (alive >= 12)
        multiplier = 1.55f;
    else if (alive >= 8)
        multiplier = 2.25f;
    else if (alive >= 5)
        multiplier = 3.15f;
    else
        multiplier = 4.50f;

    return std::clamp<DWORD>(static_cast<DWORD>(static_cast<float>(base) * multiplier), 500u, 12000u);
}

float distantSimulationDistanceForAliveCount(int alive)
{
    float base = std::max(60.0f, g_settings.distantBattleSimulationDistance);
    if (!g_runtime.deathmatch && alive <= 2)
        return std::max(base, 380.0f);
    if (!g_runtime.deathmatch && alive <= 4)
        return std::max(base, 260.0f);
    return base;
}

void deleteSimulatedSurvivalFighterEntity(Fighter& fighter, DWORD t)
{
    removeFighterBlip(fighter);
    resetScriptedActionState(fighter, true);
    if (!exists(fighter.ped))
    {
        fighter.ped = 0;
        fighter.blip = 0;
        fighter.corpseDeleted = true;
        fighter.corpseCleanupQueued = false;
        return;
    }

    if (fighter.deathPosition.x == 0.0f && fighter.deathPosition.y == 0.0f && fighter.deathPosition.z == 0.0f)
        fighter.deathPosition = entityCoords(fighter.ped);
    if (!fighter.diedAt)
        fighter.diedAt = t;
    if (!fighter.droppedWeaponObject)
        fighter.droppedWeaponObject = trackedWeaponObjectForPed(fighter.ped);

    if (safelyDeleteBattleCorpse(fighter.ped, fighter.droppedWeaponObject))
    {
        fighter.blip = 0;
        fighter.corpseDeleted = true;
        fighter.corpseCleanupQueued = false;
        ++g_runtime.corpsesRemoved;
        return;
    }

    ENTITY::SET_ENTITY_HEALTH(fighter.ped, 0, 0);
    fighter.corpseCleanupQueued = true;
    fighter.corpseDeleted = false;
    fighter.corpseCleanupEligibleAt = t;
}

void deleteSimulatedDeathmatchFighterEntity(Fighter& fighter, DWORD t)
{
    removeFighterBlip(fighter);
    resetScriptedActionState(fighter, true);
    if (deleteDeathmatchPedEntity(fighter))
    {
        fighter.pendingRespawn = true;
        fighter.respawnState = DeathmatchRespawnState::WaitingForRespawn;
        fighter.corpseDeleteAt = 0;
        return;
    }

    if (exists(fighter.ped))
        ENTITY::SET_ENTITY_HEALTH(fighter.ped, 0, 0);
    fighter.corpseDeleteAt = t + 150u;
}

bool recordSimulatedFighterDeath(int victimIndex, int killerIndex, DWORD t)
{
    if (victimIndex < 0 || victimIndex >= static_cast<int>(g_runtime.fighters.size()))
        return false;

    Fighter& victim = g_runtime.fighters[static_cast<size_t>(victimIndex)];
    if (victim.deathRecorded || !isAlive(victim))
        return false;

    victim.deathRecorded = true;
    if (g_runtime.deathmatch)
    {
        ++victim.deaths;
    }
    else
    {
        int aliveAfterDeath = playerAliveInBattle() ? 1 : 0;
        for (int i = 0; i < static_cast<int>(g_runtime.fighters.size()); ++i)
        {
            if (i != victimIndex && isAlive(g_runtime.fighters[static_cast<size_t>(i)]))
                ++aliveAfterDeath;
        }
        victim.finishPosition = std::max(1, aliveAfterDeath + 1);
    }

    bool killAttributed = false;
    if (killerIndex >= 0 && killerIndex < static_cast<int>(g_runtime.fighters.size()) && killerIndex != victimIndex)
    {
        Fighter& killer = g_runtime.fighters[static_cast<size_t>(killerIndex)];
        if (isAlive(killer) && !sameSimulatedBattleSide(killer, victim))
        {
            ++killer.kills;
            killAttributed = true;
            if (g_runtime.spectatorCameraActive && g_runtime.spectatorTargetIndex == victimIndex)
                g_runtime.spectatorTargetIndex = killerIndex;
        }
    }

    if (!killAttributed && g_runtime.spectatorCameraActive && g_runtime.spectatorTargetIndex == victimIndex)
        g_runtime.spectatorTargetIndex = -1;

    if (g_runtime.deathmatch)
    {
        beginDeathmatchRespawnBookkeeping(victim, t);
        deleteSimulatedDeathmatchFighterEntity(victim, t);
    }
    else
    {
        initialiseFighterCorpseState(victim, t);
        deleteSimulatedSurvivalFighterEntity(victim, t);
    }

    ++g_runtime.simulatedBattleDeaths;
    return true;
}

bool updateDistantBattleSimulation(DWORD t)
{
    if (!distantBattleSimulationCanKeepBattleAlive())
    {
        g_runtime.distantSimulationEligibleSince = 0;
        g_runtime.nextDistantSimulationAt = 0;
        return false;
    }

    Vec3 reference = distantSimulationReferencePosition();
    int alive = 0;
    for (const Fighter& fighter : g_runtime.fighters)
    {
        if (!isAlive(fighter))
            continue;
        ++alive;
    }

    float distanceLimit = distantSimulationDistanceForAliveCount(alive);
    std::vector<int> outOfRangeCombatants = distantSimulationOutOfRangeIndices(reference, distanceLimit);
    if (alive < 2 ||
        (g_runtime.freeForAll && !g_runtime.deathmatch && alive <= 2) ||
        distantSimulationEligibleSideCount(outOfRangeCombatants) < 2 ||
        !hasDistantSimulationVictimCandidate(outOfRangeCombatants))
    {
        g_runtime.distantSimulationEligibleSince = 0;
        g_runtime.nextDistantSimulationAt = 0;
        return false;
    }

    if (g_runtime.distantSimulationEligibleSince == 0)
    {
        g_runtime.distantSimulationEligibleSince = t;
        g_runtime.nextDistantSimulationAt = t + g_settings.distantBattleSimulationDelayMs;
        return true;
    }

    if (t < g_runtime.nextDistantSimulationAt)
        return true;

    int victimIndex = chooseDistantSimulationVictimIndex(outOfRangeCombatants, reference, distanceLimit);
    int killerIndex = chooseDistantSimulationKillerIndex(victimIndex, outOfRangeCombatants);
    if (recordSimulatedFighterDeath(victimIndex, killerIndex, t))
    {
        DWORD scaledTick = distantSimulationTickForAliveCount(alive);
        DWORD jitter = scaledTick > 1000u ?
            static_cast<DWORD>(randomRange(0, static_cast<int>(scaledTick / 4u))) :
            0u;
        g_runtime.nextDistantSimulationAt = t + scaledTick + jitter;
    }
    else
    {
        g_runtime.nextDistantSimulationAt = t + 1000u;
    }
    return true;
}

void resetFighterCorpseState(Fighter& fighter)
{
    fighter.diedAt = 0;
    fighter.corpseCleanupEligibleAt = 0;
    fighter.lastCorpseCleanupCheck = 0;
    fighter.corpseCleanupQueued = false;
    fighter.corpseDeleted = false;
    fighter.deathPosition = {};
    fighter.droppedWeaponObject = 0;
}

void registerDetachedCorpseFromFighter(const Fighter& fighter, Ped corpsePed, Object droppedWeaponObject)
{
    if (!exists(corpsePed))
        return;

    BattleCorpse corpse{};
    corpse.ped = corpsePed;
    corpse.droppedWeaponObject = droppedWeaponObject;
    corpse.diedAt = fighter.diedAt ? fighter.diedAt : now();
    corpse.cleanupEligibleAt = corpse.diedAt + corpseMinimumLifetime(fighter.difficulty);
    corpse.position = fighter.deathPosition.x != 0.0f || fighter.deathPosition.y != 0.0f || fighter.deathPosition.z != 0.0f ?
        fighter.deathPosition :
        entityCoords(corpsePed);
    corpse.elite = isEliteCorpseDifficulty(fighter.difficulty);
    for (int i = 0; i < static_cast<int>(g_runtime.fighters.size()); ++i)
    {
        if (&g_runtime.fighters[static_cast<size_t>(i)] == &fighter)
        {
            corpse.ownerIndex = i;
            break;
        }
    }
    g_runtime.battleCorpses.push_back(corpse);
}

int existingBattleCorpseCount()
{
    int count = 0;
    for (const Fighter& fighter : g_runtime.fighters)
    {
        if (fighter.deathRecorded &&
            fighter.corpseCleanupQueued &&
            !fighter.corpseDeleted &&
            exists(fighter.ped) &&
            (PED::IS_PED_DEAD_OR_DYING(fighter.ped, true) || PED::IS_PED_FATALLY_INJURED(fighter.ped)))
        {
            ++count;
        }
    }

    for (const BattleCorpse& corpse : g_runtime.battleCorpses)
    {
        if (!corpse.deleted && exists(corpse.ped))
            ++count;
    }
    return count;
}

bool tryDeleteFighterCorpse(Fighter& fighter, DWORD t, int corpseCount, bool force)
{
    if (!fighter.deathRecorded ||
        !fighter.corpseCleanupQueued ||
        fighter.corpseDeleted ||
        fighter.respawnAt != 0 ||
        !exists(fighter.ped))
    {
        return false;
    }

    bool dead = PED::IS_PED_DEAD_OR_DYING(fighter.ped, true) || PED::IS_PED_FATALLY_INJURED(fighter.ped);
    if (!dead || fighter.cinematicRecoveryActive)
        return false;

    fighter.lastCorpseCleanupCheck = t;
    bool elite = isEliteCorpseDifficulty(fighter.difficulty);
    if (!force && !safeToCleanupCorpse(fighter.ped, fighter.deathPosition, fighter.diedAt, fighter.corpseCleanupEligibleAt, elite, t, corpseCount))
        return false;

    Ped corpse = fighter.ped;
    Object dropped = fighter.droppedWeaponObject;
    bool deleted = safelyDeleteBattleCorpse(corpse, dropped);
    fighter.ped = corpse;
    fighter.droppedWeaponObject = dropped;
    if (deleted)
    {
        fighter.corpseDeleted = true;
        fighter.corpseCleanupQueued = false;
        ++g_runtime.corpsesRemoved;
        return true;
    }

    ++g_runtime.corpseDeletionRetries;
    return false;
}

bool tryDeleteDetachedCorpse(BattleCorpse& corpse, DWORD t, int corpseCount, bool force)
{
    if (corpse.deleted || !corpse.ped)
        return false;
    if (!exists(corpse.ped))
    {
        corpse.deleted = true;
        corpse.ped = 0;
        corpse.droppedWeaponObject = 0;
        return false;
    }

    corpse.lastCleanupCheck = t;
    if (!force && !safeToCleanupCorpse(corpse.ped, corpse.position, corpse.diedAt, corpse.cleanupEligibleAt, corpse.elite, t, corpseCount))
        return false;

    bool deleted = safelyDeleteBattleCorpse(corpse.ped, corpse.droppedWeaponObject);
    if (deleted)
    {
        corpse.deleted = true;
        ++g_runtime.corpsesRemoved;
        return true;
    }

    ++corpse.retries;
    ++g_runtime.corpseDeletionRetries;
    if (corpse.retries > 8)
        ++g_runtime.corpseDeletionFailures;
    return false;
}

void updateBattleCorpseCleanup(DWORD t)
{
    if (!g_settings.enableCorpseCleanup || battlePreparationActive())
        return;
    if (g_runtime.nextCorpseCleanupPassAt != 0 && t < g_runtime.nextCorpseCleanupPassAt)
        return;
    g_runtime.nextCorpseCleanupPassAt = t + g_settings.corpseCleanupCheckMs;

    int corpseCount = existingBattleCorpseCount();
    if (corpseCount <= 0)
        return;

    bool overPreferred = corpseCount > g_settings.preferredMaximumCorpses;
    bool overHard = corpseCount > g_settings.hardMaximumCorpses;
    int deletesRemaining = overHard ? kCorpseCleanupDeletesPerTick : (overPreferred ? 1 : 1);

    int processed = 0;
    while (processed < kCorpseCleanupFightersPerTick && !g_runtime.fighters.empty() && deletesRemaining > 0)
    {
        if (g_runtime.corpseCleanupCursor >= g_runtime.fighters.size())
            g_runtime.corpseCleanupCursor = 0;
        Fighter& fighter = g_runtime.fighters[g_runtime.corpseCleanupCursor++];
        bool force = overHard && fighter.diedAt != 0 && t - fighter.diedAt >= g_settings.maximumCorpseLifetimeMs;
        if (tryDeleteFighterCorpse(fighter, t, corpseCount, force))
        {
            --corpseCount;
            --deletesRemaining;
        }
        ++processed;
    }

    processed = 0;
    while (processed < kCorpseCleanupDetachedPerTick && !g_runtime.battleCorpses.empty() && deletesRemaining > 0)
    {
        if (g_runtime.detachedCorpseCleanupCursor >= g_runtime.battleCorpses.size())
            g_runtime.detachedCorpseCleanupCursor = 0;
        BattleCorpse& corpse = g_runtime.battleCorpses[g_runtime.detachedCorpseCleanupCursor++];
        bool force = overHard && corpse.diedAt != 0 && t - corpse.diedAt >= g_settings.maximumCorpseLifetimeMs;
        if (tryDeleteDetachedCorpse(corpse, t, corpseCount, force))
        {
            --corpseCount;
            --deletesRemaining;
        }
        ++processed;
    }

    if (!g_runtime.battleCorpses.empty() && g_runtime.battleCorpses.size() > 96)
    {
        g_runtime.battleCorpses.erase(
            std::remove_if(
                g_runtime.battleCorpses.begin(),
                g_runtime.battleCorpses.end(),
                [](const BattleCorpse& corpse) { return corpse.deleted || !exists(corpse.ped); }),
            g_runtime.battleCorpses.end());
        if (g_runtime.detachedCorpseCleanupCursor > g_runtime.battleCorpses.size())
            g_runtime.detachedCorpseCleanupCursor = 0;
    }
}

Fighter* fighterFromPed(Ped ped)
{
    if (!ped)
        return nullptr;

    for (Fighter& fighter : g_runtime.fighters)
    {
        if (fighter.ped == ped)
            return &fighter;
    }
    return nullptr;
}

void resetPlayerDamageAttribution()
{
    g_runtime.playerRecentDamagerPed = 0;
    g_runtime.playerRecentDamagerAt = 0;
    Ped player = playerPed();
    g_runtime.playerLastObservedHealth = exists(player) ? ENTITY::GET_ENTITY_HEALTH(player) : 0;
}

void updatePlayerDamageAttribution(bool playerDead)
{
    if (!g_runtime.battleActive || !g_runtime.playerWasParticipant)
        return;

    Ped player = playerPed();
    if (!exists(player))
        return;

    DWORD t = now();
    int health = ENTITY::GET_ENTITY_HEALTH(player);
    if (g_runtime.playerLastObservedHealth <= 0)
    {
        g_runtime.playerLastObservedHealth = health;
        return;
    }

    bool healthDropped = health < g_runtime.playerLastObservedHealth;
    bool damagedByAnyPed = ENTITY::HAS_ENTITY_BEEN_DAMAGED_BY_ANY_PED(player) != 0;
    if (!healthDropped && !damagedByAnyPed)
    {
        g_runtime.playerLastObservedHealth = health;
        return;
    }

    Fighter* best = nullptr;
    float bestScore = 99999999.0f;
    Vec3 playerPos = entityCoords(player);
    for (Fighter& fighter : g_runtime.fighters)
    {
        if (!exists(fighter.ped) ||
            fighter.ped == player ||
            !ENTITY::HAS_ENTITY_BEEN_DAMAGED_BY_ENTITY(player, fighter.ped, true, true))
        {
            continue;
        }

        float dist = distanceSquared(playerPos, entityCoords(fighter.ped));
        float score = dist;
        if (PED::IS_PED_SHOOTING(fighter.ped))
            score -= 2400.0f;
        if (fighter.currentTarget == player)
            score -= 900.0f;
        if (fighter.lastShotTask != 0 && t - fighter.lastShotTask < 1200u)
            score -= 500.0f;
        if (score < bestScore)
        {
            best = &fighter;
            bestScore = score;
        }
    }

    if (best)
    {
        g_runtime.playerRecentDamagerPed = best->ped;
        g_runtime.playerRecentDamagerAt = t;
    }

    g_runtime.playerLastObservedHealth = health;
    if (!playerDead)
        ENTITY::CLEAR_ENTITY_LAST_DAMAGE_ENTITY(player);
}

Fighter* findPlayerDeathKiller()
{
    Ped player = playerPed();
    if (!exists(player))
        return nullptr;

    Entity source = PED::GET_PED_SOURCE_OF_DEATH(player);
    if (source)
    {
        if (Fighter* fighter = fighterFromPed(static_cast<Ped>(source)))
            return fighter;
    }

    DWORD t = now();
    if (g_runtime.playerRecentDamagerPed &&
        g_runtime.playerRecentDamagerAt != 0 &&
        t - g_runtime.playerRecentDamagerAt < 6500u)
    {
        if (Fighter* fighter = fighterFromPed(g_runtime.playerRecentDamagerPed))
            return fighter;
    }

    Vec3 playerPos = entityCoords(player);
    Fighter* best = nullptr;
    float bestDistance = 99999999.0f;
    for (Fighter& fighter : g_runtime.fighters)
    {
        if (!exists(fighter.ped) ||
            !ENTITY::HAS_ENTITY_BEEN_DAMAGED_BY_ENTITY(player, fighter.ped, true, true))
        {
            continue;
        }

        float dist = distanceSquared(playerPos, entityCoords(fighter.ped));
        if (dist < bestDistance)
        {
            best = &fighter;
            bestDistance = dist;
        }
    }

    return best;
}

void recordPlayerKilledByNpc()
{
    if (!g_runtime.playerWasParticipant || (!g_runtime.deathmatch && g_runtime.playerKillerRecorded))
        return;

    for (Fighter& fighter : g_runtime.fighters)
        fighter.killedPlayer = false;
    g_runtime.playerKillerPed = 0;
    g_runtime.playerKillerName.clear();
    g_runtime.playerKillerRecorded = false;
    g_runtime.preferredSpectatorTargetIndex = -1;

    Fighter* killer = findPlayerDeathKiller();
    if (!killer)
        return;

    ++killer->kills;
    killer->killedPlayer = true;
    g_runtime.playerKillerPed = killer->ped;
    g_runtime.playerKillerName = killer->displayName.empty() ? killer->baseName : killer->displayName;
    for (int i = 0; i < static_cast<int>(g_runtime.fighters.size()); ++i)
    {
        if (&g_runtime.fighters[static_cast<size_t>(i)] == killer)
        {
            g_runtime.preferredSpectatorTargetIndex = i;
            break;
        }
    }
    g_runtime.playerKillerRecorded = true;
}

void recordPlayerEliminationPosition()
{
    if (!g_runtime.playerWasParticipant || g_runtime.playerFinishPosition > 0)
        return;

    g_runtime.playerFinishPosition = std::max(1, aliveFighterCount() + 1);
}

std::vector<std::string> buildTeamPositionLeaderboardLines()
{
    struct TeamEntry
    {
        int team = 0;
        int kills = 0;
        int survivalScore = 999999;
        int position = 1;
        bool active = false;
        bool killedPlayer = false;
    };

    std::array<TeamEntry, kTeamCount> teams{};
    for (int i = 0; i < kTeamCount; ++i)
        teams[static_cast<size_t>(i)].team = i;

    int fallbackPosition = std::max(1, aliveFighterCount() + (playerAliveInBattle() ? 1 : 0) + 1);
    if (g_runtime.playerWasParticipant && g_runtime.playerTeam >= 0 && g_runtime.playerTeam < kTeamCount)
    {
        TeamEntry& team = teams[static_cast<size_t>(g_runtime.playerTeam)];
        team.active = true;
        team.kills += g_runtime.playerKills;
        int playerPosition = g_runtime.playerFinishPosition > 0 ? g_runtime.playerFinishPosition : (playerAliveInBattle() ? 1 : fallbackPosition);
        team.survivalScore = std::min(team.survivalScore, playerPosition);
    }

    for (const Fighter& fighter : g_runtime.fighters)
    {
        if (fighter.team < 0 || fighter.team >= kTeamCount)
            continue;

        TeamEntry& team = teams[static_cast<size_t>(fighter.team)];
        team.active = true;
        team.kills += fighter.kills;
        if (fighter.killedPlayer)
            team.killedPlayer = true;
        int fighterPosition = fighter.finishPosition > 0 ? fighter.finishPosition : (isAlive(fighter) ? 1 : fallbackPosition);
        team.survivalScore = std::min(team.survivalScore, fighterPosition);
    }

    std::vector<TeamEntry> entries;
    entries.reserve(kTeamCount);
    for (const TeamEntry& team : teams)
    {
        if (!team.active)
            continue;
        entries.push_back(team);
    }

    std::sort(entries.begin(), entries.end(), [](const TeamEntry& a, const TeamEntry& b) {
        if (a.survivalScore != b.survivalScore)
            return a.survivalScore < b.survivalScore;
        return a.team < b.team;
    });

    int displayedPosition = 0;
    int previousScore = -1;
    for (TeamEntry& entry : entries)
    {
        if (entry.survivalScore != previousScore)
        {
            ++displayedPosition;
            previousScore = entry.survivalScore;
        }
        entry.position = displayedPosition;
    }

    g_runtime.leaderboardTotal = static_cast<int>(entries.size());
    std::vector<std::string> lines;
    lines.reserve(entries.size());
    for (const TeamEntry& entry : entries)
    {
        char buffer[128]{};
        std::snprintf(
            buffer,
            sizeof(buffer),
            "%d. Team %d - %d %s",
            entry.position,
            entry.team + 1,
            entry.kills,
            entry.kills == 1 ? "kill" : "kills");
        if (entry.killedPlayer)
            std::snprintf(buffer + std::strlen(buffer), sizeof(buffer) - std::strlen(buffer), " (killed you)");
        lines.emplace_back(buffer);
    }
    return lines;
}

std::vector<std::string> buildDeathmatchTeamLeaderboardLines()
{
    struct TeamEntry
    {
        int team = 0;
        int kills = 0;
        int deaths = 0;
        bool active = false;
        bool killedPlayer = false;
    };

    std::array<TeamEntry, kTeamCount> teams{};
    for (int i = 0; i < kTeamCount; ++i)
        teams[static_cast<size_t>(i)].team = i;

    if (g_runtime.playerWasParticipant && g_runtime.playerTeam >= 0 && g_runtime.playerTeam < kTeamCount)
    {
        TeamEntry& team = teams[static_cast<size_t>(g_runtime.playerTeam)];
        team.active = true;
        team.kills += g_runtime.playerKills;
        team.deaths += g_runtime.playerDeaths;
    }

    for (const Fighter& fighter : g_runtime.fighters)
    {
        if (fighter.team < 0 || fighter.team >= kTeamCount)
            continue;

        TeamEntry& team = teams[static_cast<size_t>(fighter.team)];
        team.active = true;
        team.kills += fighter.kills;
        team.deaths += fighter.deaths;
        team.killedPlayer = team.killedPlayer || fighter.killedPlayer;
    }

    std::vector<TeamEntry> entries;
    entries.reserve(kTeamCount);
    for (const TeamEntry& team : teams)
    {
        if (team.active)
            entries.push_back(team);
    }

    std::sort(entries.begin(), entries.end(), [](const TeamEntry& a, const TeamEntry& b) {
        if (a.kills != b.kills)
            return a.kills > b.kills;
        if (kdRatio(a.kills, a.deaths) != kdRatio(b.kills, b.deaths))
            return kdRatio(a.kills, a.deaths) > kdRatio(b.kills, b.deaths);
        return a.team < b.team;
    });

    g_runtime.leaderboardTotal = static_cast<int>(entries.size());
    std::vector<std::string> lines;
    lines.reserve(entries.size());
    for (int i = 0; i < static_cast<int>(entries.size()); ++i)
    {
        const TeamEntry& entry = entries[static_cast<size_t>(i)];
        char buffer[144]{};
        std::snprintf(
            buffer,
            sizeof(buffer),
            "%d. Team %d%s - %dK %dD KD %s",
            i + 1,
            entry.team + 1,
            entry.killedPlayer ? " (killed you)" : "",
            entry.kills,
            entry.deaths,
            kdText(entry.kills, entry.deaths).c_str());
        lines.emplace_back(buffer);
    }
    return lines;
}

std::vector<std::string> buildDeathmatchLeaderboardLines(LeaderboardMode mode)
{
    if (!g_runtime.freeForAll && mode == LeaderboardMode::Position)
        return buildDeathmatchTeamLeaderboardLines();

    struct Entry
    {
        std::string name;
        Hash group = 0;
        int kills = 0;
        int deaths = 0;
        int order = 0;
        bool killedPlayer = false;
    };

    std::vector<Entry> entries;
    entries.reserve(g_runtime.fighters.size() + 1);
    int order = 0;
    if (g_runtime.playerWasParticipant)
        entries.push_back({ playerLeaderboardName(), g_runtime.freeForAll ? g_runtime.playerFreeForAllGroup : 0, g_runtime.playerKills, g_runtime.playerDeaths, order++, false });

    for (const Fighter& fighter : g_runtime.fighters)
    {
        std::string name = fighter.displayName.empty() ? "Battle Fighter" : fighter.displayName;
        entries.push_back({ name, g_runtime.freeForAll ? fighter.group : 0, fighter.kills, fighter.deaths, order++, fighter.killedPlayer });
    }

    if (g_runtime.freeForAll && g_runtime.freeForAllTeamSize > 1 && mode == LeaderboardMode::Position)
    {
        struct GroupEntry
        {
            Hash group = 0;
            int kills = 0;
            int deaths = 0;
            int order = 0;
            int position = 1;
        };

        std::vector<GroupEntry> groups;
        groups.reserve(entries.size());
        for (const Entry& entry : entries)
        {
            if (!entry.group)
                continue;

            auto it = std::find_if(groups.begin(), groups.end(), [&](const GroupEntry& groupEntry) {
                return groupEntry.group == entry.group;
            });

            if (it == groups.end())
            {
                groups.push_back({ entry.group, groupKillScore(entry.group), groupDeathScore(entry.group), entry.order, 1 });
            }
            else
            {
                it->order = std::min(it->order, entry.order);
            }
        }

        std::sort(groups.begin(), groups.end(), [](const GroupEntry& a, const GroupEntry& b) {
            if (a.kills != b.kills)
                return a.kills > b.kills;
            if (kdRatio(a.kills, a.deaths) != kdRatio(b.kills, b.deaths))
                return kdRatio(a.kills, a.deaths) > kdRatio(b.kills, b.deaths);
            if (a.deaths != b.deaths)
                return a.deaths < b.deaths;
            return a.order < b.order;
        });

        int displayedPosition = 0;
        int previousKills = -1;
        int previousDeaths = -1;
        for (GroupEntry& group : groups)
        {
            if (group.kills != previousKills || group.deaths != previousDeaths)
            {
                ++displayedPosition;
                previousKills = group.kills;
                previousDeaths = group.deaths;
            }
            group.position = displayedPosition;
        }

        std::sort(entries.begin(), entries.end(), [&](const Entry& a, const Entry& b) {
            auto groupForA = std::find_if(groups.begin(), groups.end(), [&](const GroupEntry& groupEntry) { return groupEntry.group == a.group; });
            auto groupForB = std::find_if(groups.begin(), groups.end(), [&](const GroupEntry& groupEntry) { return groupEntry.group == b.group; });
            int posA = groupForA != groups.end() ? groupForA->position : 9999;
            int posB = groupForB != groups.end() ? groupForB->position : 9999;
            if (posA != posB)
                return posA < posB;
            int orderA = groupForA != groups.end() ? groupForA->order : a.order;
            int orderB = groupForB != groups.end() ? groupForB->order : b.order;
            if (orderA != orderB)
                return orderA < orderB;
            return a.order < b.order;
        });

        g_runtime.leaderboardTotal = static_cast<int>(entries.size());
        int visibleEntries = std::min(g_runtime.leaderboardTotal, kLeaderboardMaxEntries);
        std::vector<std::string> lines;
        lines.reserve(static_cast<size_t>(visibleEntries));
        for (int i = 0; i < visibleEntries; ++i)
        {
            const Entry& entry = entries[static_cast<size_t>(i)];
            auto group = std::find_if(groups.begin(), groups.end(), [&](const GroupEntry& groupEntry) {
                return groupEntry.group == entry.group;
            });
            int groupKills = group != groups.end() ? group->kills : entry.kills;
            int groupDeaths = group != groups.end() ? group->deaths : entry.deaths;
            int groupPosition = group != groups.end() ? group->position : i + 1;

            char buffer[192]{};
            std::snprintf(
                buffer,
                sizeof(buffer),
                "%d. %s%s - K:%d D:%d KD:%s",
                groupPosition,
                entry.name.c_str(),
                entry.killedPlayer ? " (killed you)" : "",
                groupKills,
                groupDeaths,
                kdText(groupKills, groupDeaths).c_str());
            lines.emplace_back(buffer);
        }
        return lines;
    }

    std::sort(entries.begin(), entries.end(), [mode](const Entry& a, const Entry& b) {
        if (mode == LeaderboardMode::Position && g_runtime.freeForAll && g_runtime.freeForAllTeamSize <= 1)
        {
            float aKd = kdRatio(a.kills, a.deaths);
            float bKd = kdRatio(b.kills, b.deaths);
            if (aKd != bKd)
                return aKd > bKd;
            if (a.kills != b.kills)
                return a.kills > b.kills;
            if (a.deaths != b.deaths)
                return a.deaths < b.deaths;
            return a.order < b.order;
        }

        if (a.kills != b.kills)
            return a.kills > b.kills;
        if (kdRatio(a.kills, a.deaths) != kdRatio(b.kills, b.deaths))
            return kdRatio(a.kills, a.deaths) > kdRatio(b.kills, b.deaths);
        if (a.deaths != b.deaths)
            return a.deaths < b.deaths;
        return a.order < b.order;
    });

    g_runtime.leaderboardTotal = static_cast<int>(entries.size());
    int visibleEntries = std::min(g_runtime.leaderboardTotal, kLeaderboardMaxEntries);
    std::vector<std::string> lines;
    lines.reserve(static_cast<size_t>(visibleEntries));
    for (int i = 0; i < visibleEntries; ++i)
    {
        const Entry& entry = entries[static_cast<size_t>(i)];
        char buffer[192]{};
        std::snprintf(
            buffer,
            sizeof(buffer),
            "%d. %s%s - K:%d D:%d KD:%s",
            i + 1,
            entry.name.c_str(),
            entry.killedPlayer ? " (killed you)" : "",
            entry.kills,
            entry.deaths,
            kdText(entry.kills, entry.deaths).c_str());
        lines.emplace_back(buffer);
    }
    return lines;
}

std::vector<std::string> buildLeaderboardLines(LeaderboardMode mode)
{
    if (g_runtime.deathmatch)
        return buildDeathmatchLeaderboardLines(mode);

    if (mode == LeaderboardMode::Position && !g_runtime.freeForAll)
        return buildTeamPositionLeaderboardLines();

    struct Entry
    {
        std::string name;
        Hash group = 0;
        int kills = 0;
        int position = 1;
        int order = 0;
        bool killedPlayer = false;
    };

    std::vector<Entry> entries;
    entries.reserve(g_runtime.fighters.size() + 1);

    int order = 0;
    if (g_runtime.playerWasParticipant)
    {
        int position = g_runtime.playerFinishPosition > 0 ? g_runtime.playerFinishPosition : 1;
        Hash group = g_runtime.freeForAll ? g_runtime.playerFreeForAllGroup : 0;
        entries.push_back({ playerLeaderboardName(), group, g_runtime.playerKills, position, order++, false });
    }

    for (const Fighter& fighter : g_runtime.fighters)
    {
        std::string name = fighter.displayName.empty() ? "Battle Fighter" : fighter.displayName;
        int position = fighter.finishPosition > 0 ? fighter.finishPosition : (isAlive(fighter) ? 1 : std::max(1, aliveFighterCount() + 1));
        Hash group = g_runtime.freeForAll ? fighter.group : 0;
        bool killedPlayer = fighter.killedPlayer || (g_runtime.playerKillerRecorded && fighter.ped == g_runtime.playerKillerPed);
        entries.push_back({ name, group, fighter.kills, position, order++, killedPlayer });
    }

    if (mode == LeaderboardMode::Position && g_runtime.freeForAll && g_runtime.freeForAllTeamSize > 1)
    {
        struct GroupPosition
        {
            Hash group = 0;
            int survivalScore = 1;
            int position = 1;
            int order = 0;
        };

        std::vector<GroupPosition> groups;
        groups.reserve(entries.size());
        for (const Entry& entry : entries)
        {
            if (!entry.group)
                continue;

            auto it = std::find_if(groups.begin(), groups.end(), [&](const GroupPosition& groupPosition) {
                return groupPosition.group == entry.group;
            });

            if (it == groups.end())
                groups.push_back({ entry.group, entry.position, 1, entry.order });
            else
            {
                it->survivalScore = std::min(it->survivalScore, entry.position);
                it->order = std::min(it->order, entry.order);
            }
        }

        std::sort(groups.begin(), groups.end(), [](const GroupPosition& a, const GroupPosition& b) {
            if (a.survivalScore != b.survivalScore)
                return a.survivalScore < b.survivalScore;
            return a.order < b.order;
        });

        int displayedPosition = 0;
        int previousScore = -1;
        for (GroupPosition& group : groups)
        {
            if (group.survivalScore != previousScore)
            {
                ++displayedPosition;
                previousScore = group.survivalScore;
            }
            group.position = displayedPosition;
        }

        for (Entry& entry : entries)
        {
            auto it = std::find_if(groups.begin(), groups.end(), [&](const GroupPosition& groupPosition) {
                return groupPosition.group == entry.group;
            });
            if (it != groups.end())
                entry.position = it->position;
        }
    }

    std::sort(entries.begin(), entries.end(), [mode](const Entry& a, const Entry& b) {
        if (mode == LeaderboardMode::Position)
        {
            if (a.position != b.position)
                return a.position < b.position;
            if (a.kills != b.kills)
                return a.kills > b.kills;
            return a.order < b.order;
        }

        if (a.kills != b.kills)
            return a.kills > b.kills;
        return a.order < b.order;
    });

    g_runtime.leaderboardTotal = static_cast<int>(entries.size());
    int visibleEntries = std::min(g_runtime.leaderboardTotal, kLeaderboardMaxEntries);
    std::vector<std::string> lines;
    lines.reserve(static_cast<size_t>(visibleEntries));
    for (int i = 0; i < visibleEntries; ++i)
    {
        char buffer[192]{};
        const Entry& entry = entries[static_cast<size_t>(i)];
        int displayedPosition = mode == LeaderboardMode::Position ? entry.position : i + 1;
        std::snprintf(
            buffer,
            sizeof(buffer),
            "%d. %s%s - %d %s",
            displayedPosition,
            entry.name.c_str(),
            entry.killedPlayer ? " (killed you)" : "",
            entry.kills,
            entry.kills == 1 ? "kill" : "kills");
        lines.emplace_back(buffer);
    }
    return lines;
}

void refreshLeaderboardLines()
{
    if (g_runtime.leaderboardMode == LeaderboardMode::Position)
    {
        g_runtime.leaderboardLines = g_runtime.leaderboardPositionLines;
        g_runtime.leaderboardTotal = g_runtime.leaderboardPositionTotal;
        return;
    }

    g_runtime.leaderboardLines = g_runtime.leaderboardKillLines;
    g_runtime.leaderboardTotal = g_runtime.leaderboardKillTotal;
}

void clearLeaderboard()
{
    g_runtime.leaderboardLines.clear();
    g_runtime.leaderboardKillLines.clear();
    g_runtime.leaderboardPositionLines.clear();
    g_runtime.leaderboardMode = LeaderboardMode::Kills;
    g_runtime.leaderboardTotal = 0;
    g_runtime.leaderboardKillTotal = 0;
    g_runtime.leaderboardPositionTotal = 0;
    g_runtime.leaderboardUntil = 0;
}

void buildBattleLeaderboard()
{
    g_runtime.leaderboardKillLines = buildLeaderboardLines(LeaderboardMode::Kills);
    g_runtime.leaderboardKillTotal = g_runtime.leaderboardTotal;
    g_runtime.leaderboardPositionLines = buildLeaderboardLines(LeaderboardMode::Position);
    g_runtime.leaderboardPositionTotal = g_runtime.leaderboardTotal;
    g_runtime.leaderboardMode = LeaderboardMode::Kills;
    g_runtime.leaderboardUntil = 0;
    refreshLeaderboardLines();
}

void toggleLeaderboardMode()
{
    if (g_runtime.leaderboardLines.empty())
        return;

    g_runtime.leaderboardMode = g_runtime.leaderboardMode == LeaderboardMode::Kills ?
        LeaderboardMode::Position :
        LeaderboardMode::Kills;
    refreshLeaderboardLines();
    setStatus(std::string("Leaderboard: ") + leaderboardModeName(g_runtime.leaderboardMode), 3500);
}

void deleteFighters()
{
    stopSpectatorCamera();
    restorePlayerAfterBattleSpectator();
    deletePlayerBattleCorpse();

    for (Fighter& fighter : g_runtime.fighters)
    {
        resetScriptedActionState(fighter, true);
        removeFighterBlip(fighter);
        if (fighter.group && !isTeamRelationshipGroup(fighter.group) && !isFreeForAllRelationshipGroup(fighter.group))
            PED::REMOVE_RELATIONSHIP_GROUP(fighter.group);

        if (!exists(fighter.ped))
        {
            deleteTrackedWeaponObject(fighter.droppedWeaponObject);
            continue;
        }

        if (PED::IS_PED_IN_GROUP(fighter.ped))
            PED::REMOVE_PED_FROM_GROUP(fighter.ped);
        safelyDeleteBattleCorpse(fighter.ped, fighter.droppedWeaponObject);
    }

    for (BattleCorpse& corpse : g_runtime.battleCorpses)
        safelyDeleteBattleCorpse(corpse.ped, corpse.droppedWeaponObject);
    g_runtime.battleCorpses.clear();
    g_runtime.deathmatchRespawnQueue.clear();
    g_runtime.deathmatchRespawnQueueCursor = 0;
    g_runtime.fighterSnapshots.clear();

    g_runtime.fighters.clear();
    g_runtime.battleActive = false;
    g_runtime.resultAnnounced = false;
    g_runtime.initialActiveTeams = 0;
    g_runtime.neutralTeamProvokedByPlayer.fill(false);
    for (Hash group : g_runtime.freeForAllGroups)
    {
        if (group)
            PED::REMOVE_RELATIONSHIP_GROUP(group);
    }
    g_runtime.freeForAllGroups.clear();
    g_runtime.freeForAll = false;
    g_runtime.deathmatch = false;
    g_runtime.freeForAllSpectate = false;
    g_runtime.freeForAllTeamSize = 1;
    g_runtime.playerFreeForAllGroup = 0;
    g_runtime.freeForAllSpawnGroup = 0;
    g_runtime.startCountdownActive = false;
    g_runtime.startCountdownEndsAt = 0;
    g_runtime.playerParticipating = false;
    g_runtime.playerWasParticipant = false;
    g_runtime.playerDeaths = 0;
    g_runtime.playerFinishPosition = 0;
    g_runtime.playerKillerPed = 0;
    g_runtime.playerKillerName.clear();
    g_runtime.playerKillerRecorded = false;
    g_runtime.playerRecentDamagerPed = 0;
    g_runtime.playerRecentDamagerAt = 0;
    g_runtime.playerLastObservedHealth = 0;
    g_runtime.playerEliminated = false;
    g_runtime.playerSpectating = false;
    g_runtime.playerRevivePending = false;
    g_runtime.playerSafePosValid = false;
    g_runtime.playerHiddenForSpectator = false;
    g_runtime.playerScreenRepairUntil = 0;
    g_runtime.playerTeam = -1;
    g_runtime.freeForAllPlayerScatterIndex = -1;
    g_runtime.freeForAllSpawnAngle = 0.0f;
    g_runtime.relationshipsDirty = true;
    g_runtime.lastRelationshipSafetyRefresh = 0;
    g_runtime.lastRelationshipValidation = 0;
    g_runtime.nextCleanupDistanceCheck = 0;
    g_runtime.distantSimulationEligibleSince = 0;
    g_runtime.nextDistantSimulationAt = 0;
    g_runtime.simulatedBattleDeaths = 0;
    g_runtime.protectedExecutionFallbacks = 0;
    g_runtime.compactHudLine1.clear();
    g_runtime.compactHudLine2.clear();
    g_runtime.compactHudTwoLine = false;
    g_runtime.compactHudNextRefreshAt = 0;
    g_runtime.preparationPhase = BattlePreparationPhase::None;
    g_runtime.preparationCombatants.clear();
    g_runtime.preparationGroups.clear();
    g_runtime.preparationRequestedFighters = 0;
    g_runtime.preparationSpawnedFighters = 0;
    g_runtime.preparationExpectedGroups = 0;
    g_runtime.preparationSetIndex = 0;
    g_runtime.preparationSetMember = 0;
    g_runtime.preparationGlobalSpawnIndex = 0;
    g_runtime.preparationSquadIndex = 0;
    g_runtime.preparationFighterIndex = 0;
    g_runtime.preparationRelationshipPlayerIndex = 0;
    g_runtime.preparationRelationshipGroupA = 0;
    g_runtime.preparationRelationshipGroupB = 1;
    g_runtime.preparationRelationshipSettersDone = 0;
    g_runtime.preparationRelationshipSettersTotal = 0;
    g_runtime.preparationMaxGroupsPerFrame = 0;
    g_runtime.preparationMaxRelationshipSettersPerFrame = 0;
    g_runtime.preparationMaxFightersPerFrame = 0;
    g_runtime.preparationGroupCreationFailed = false;
    g_runtime.corpseCleanupCursor = 0;
    g_runtime.detachedCorpseCleanupCursor = 0;
    g_runtime.nextCorpseCleanupPassAt = 0;
    g_runtime.nextDeathmatchRespawnAllowedAt = 0;
    g_runtime.nextFighterSnapshotRefreshAt = 0;
    g_runtime.nextDeathmatchDiagnosticsAt = 0;
    g_runtime.deathmatchRespawnsThisFrame = 0;
    g_runtime.fullRetargetsThisFrame = 0;
    g_runtime.deathmatchMaxRespawnsInFrame = 0;
    g_runtime.deathmatchRespawnsCreated = 0;
    g_runtime.deathmatchRespawnAllocationFailures = 0;
    g_runtime.deathmatchRetargetsRequested = 0;
    g_runtime.deathmatchRetargetsProcessed = 0;
    g_runtime.deathmatchRetargetsDeferred = 0;
    g_runtime.targetScansUsingSnapshots = 0;
    g_runtime.targetScansWithoutSnapshots = 0;
    g_runtime.fighterSnapshotRefreshes = 0;
    g_runtime.trackedDroppedWeaponsDeleted = 0;
    g_runtime.corpsesRemoved = 0;
    g_runtime.corpseDeletionRetries = 0;
    g_runtime.corpseDeletionFailures = 0;
    g_runtime.staleTargetReferencesCleared = 0;
    stopBossDodgeDeadEyeSuppression();
    setBattleRespawnOverride(false);
    restoreWantedAfterBattle();
}

void removeRelationshipGroups()
{
    for (Hash& group : g_runtime.groups)
    {
        if (group)
            PED::REMOVE_RELATIONSHIP_GROUP(group);
        group = 0;
    }
}

void clearBattle()
{
    bool wasPreparing = battlePreparationActive();
    bool hadFighters = !wasPreparing && !g_runtime.fighters.empty();
    if (hadFighters)
    {
        buildBattleLeaderboard();
        g_menu.open = false;
        refillPlayerHealthAndCoresIfAlive();
    }

    deleteFighters();
    removeRelationshipGroups();
    clearAllManualTeamSpawns();
    setStatus(wasPreparing ? "Battle preparation cancelled" : (hadFighters ? "Battle cleared - leaderboard shown" : "Battle cleared"));
}

bool isAlive(const Fighter& fighter)
{
    return exists(fighter.ped) &&
        (fighter.cinematicRecoveryActive ||
         (!PED::IS_PED_DEAD_OR_DYING(fighter.ped, true) && !PED::IS_PED_FATALLY_INJURED(fighter.ped)));
}

bool isPlayerBattleRoyaleSquadmate(const Fighter& fighter)
{
    return freeForAllActive() &&
        g_runtime.playerParticipating &&
        !g_runtime.freeForAllSpectate &&
        !g_runtime.playerEliminated &&
        g_runtime.playerFreeForAllGroup &&
        fighter.group == g_runtime.playerFreeForAllGroup;
}

bool isNpcBattleRoyaleSquadmate(const Fighter& fighter)
{
    if (!freeForAllActive() ||
        g_runtime.freeForAllTeamSize <= 1 ||
        !fighter.group)
    {
        return false;
    }

    if (isPlayerBattleRoyaleSquadmate(fighter))
        return false;

    return true;
}

void playerSquadFollowOffsets(int slot, float& sideOffset, float& backOffset)
{
    switch (std::max(0, slot) % 4)
    {
    case 0:
        sideOffset = -2.1f;
        backOffset = -1.7f;
        break;
    case 1:
        sideOffset = 2.1f;
        backOffset = -1.7f;
        break;
    case 2:
        sideOffset = 0.0f;
        backOffset = -3.2f;
        break;
    default:
        sideOffset = 3.0f;
        backOffset = -3.0f;
        break;
    }
}

void battleRoyaleSquadOffsets(int slot, float& sideOffset, float& backOffset)
{
    switch (std::max(0, slot) % 4)
    {
    case 0:
        sideOffset = 0.0f;
        backOffset = 0.0f;
        break;
    case 1:
        sideOffset = -2.2f;
        backOffset = -1.5f;
        break;
    case 2:
        sideOffset = 2.2f;
        backOffset = -1.5f;
        break;
    default:
        sideOffset = 0.0f;
        backOffset = -3.0f;
        break;
    }
}

Vec3 offsetFromHeading(Vec3 anchor, float headingRadians, float sideOffset, float forwardOffset)
{
    float side = headingRadians + (kPi * 0.5f);
    Vec3 pos{
        anchor.x + std::sin(headingRadians) * forwardOffset + std::sin(side) * sideOffset,
        anchor.y + std::cos(headingRadians) * forwardOffset + std::cos(side) * sideOffset,
        anchor.z
    };
    snapToGround(pos);
    return pos;
}

Vec3 playerOffsetPosition(float sideOffset, float forwardOffset)
{
    Ped player = playerPed();
    Vec3 playerPos = entityCoords(player);
    float heading = ENTITY::GET_ENTITY_HEADING(player) * (kPi / 180.0f);
    float side = heading + (kPi * 0.5f);
    Vec3 pos{
        playerPos.x + std::sin(heading) * forwardOffset + std::sin(side) * sideOffset,
        playerPos.y + std::cos(heading) * forwardOffset + std::cos(side) * sideOffset,
        playerPos.z
    };
    snapToGround(pos);
    return pos;
}

void moveFighterToSquadOffset(Fighter& fighter, Vec3 anchor, float headingRadians)
{
    if (!exists(fighter.ped))
        return;

    float sideOffset{};
    float backOffset{};
    battleRoyaleSquadOffsets(fighter.battleRoyaleSquadSlot, sideOffset, backOffset);
    Vec3 pos = offsetFromHeading(anchor, headingRadians, sideOffset, backOffset);
    ENTITY::SET_ENTITY_COORDS_NO_OFFSET(fighter.ped, pos.x, pos.y, pos.z, false, false, false);
    ENTITY::SET_ENTITY_HEADING(fighter.ped, headingRadians * (180.0f / kPi));
    fighter.lastTask = 0;
    fighter.lastSquadTask = 0;
}

void moveFighterBesidePlayer(Fighter& fighter)
{
    if (!exists(fighter.ped))
        return;

    float sideOffset{};
    float backOffset{};
    playerSquadFollowOffsets(fighter.playerSquadSlot, sideOffset, backOffset);
    Vec3 pos = playerOffsetPosition(sideOffset, backOffset);
    ENTITY::SET_ENTITY_COORDS_NO_OFFSET(fighter.ped, pos.x, pos.y, pos.z, false, false, false);
    ENTITY::SET_ENTITY_HEADING(fighter.ped, ENTITY::GET_ENTITY_HEADING(playerPed()));
    fighter.lastTask = 0;
    fighter.lastFollowTask = 0;
}

void attachFighterToPlayerGroup(Fighter& fighter)
{
    if (!exists(fighter.ped))
        return;

    int playerGroup = PLAYER::GET_PLAYER_GROUP(PLAYER::PLAYER_ID());
    if (!playerGroup)
        return;

    PED::SET_PED_AS_GROUP_MEMBER(fighter.ped, playerGroup);
    PED::SET_PED_CAN_TELEPORT_TO_GROUP_LEADER(fighter.ped, playerGroup, false);
    PED::SET_GROUP_SEPARATION_RANGE(playerGroup, 20.0f);
    PED::SET_GROUP_FORMATION(playerGroup, 1);
    PED::SET_GROUP_FORMATION_SPACING(playerGroup, 1.4f, -1.7f, 2.2f);
    PED::SET_PED_GROUP_MEMBER_PASSENGER_INDEX(fighter.ped, std::max(0, fighter.playerSquadSlot));
}

bool isEnemyTargetForFighter(const Fighter& fighter, Ped target)
{
    if (!exists(target) || target == fighter.ped)
        return false;

    Ped player = playerPed();
    if (target == player)
    {
        return fighterRelationToPlayer(fighter) == PlayerRelation::Hostile &&
            !PED::IS_PED_DEAD_OR_DYING(player, true) &&
            !PED::IS_PED_FATALLY_INJURED(player);
    }

    for (const Fighter& other : g_runtime.fighters)
    {
        if (other.ped != target)
            continue;

        if (!isAlive(other))
            return false;

        if (freeForAllActive())
            return !fighter.group || !other.group || other.group != fighter.group;

        return other.team != fighter.team;
    }

    return false;
}

Ped sharedBattleRoyaleSquadTarget(const Fighter& fighter, Vec3 origin)
{
    if (!freeForAllActive() ||
        g_runtime.freeForAllTeamSize <= 1 ||
        !fighter.group)
    {
        return 0;
    }

    Ped best{};
    float bestDistance = 99999999.0f;
    for (const Fighter& teammate : g_runtime.fighters)
    {
        if (teammate.ped == fighter.ped ||
            teammate.group != fighter.group ||
            !isAlive(teammate) ||
            !isEnemyTargetForFighter(fighter, teammate.currentTarget))
        {
            continue;
        }

        float dist = distanceSquared(origin, entityCoords(teammate.currentTarget));
        if (dist < bestDistance)
        {
            best = teammate.currentTarget;
            bestDistance = dist;
        }
    }

    return best;
}

Ped closestAliveBattleRoyaleSquadmate(const Fighter& fighter, float* distanceOut = nullptr)
{
    Ped best{};
    float bestDistance = 99999999.0f;
    if (!fighter.group)
        return 0;

    Vec3 origin = entityCoords(fighter.ped);
    for (const Fighter& teammate : g_runtime.fighters)
    {
        if (teammate.ped == fighter.ped ||
            teammate.group != fighter.group ||
            !isAlive(teammate))
        {
            continue;
        }

        float dist = distanceSquared(origin, entityCoords(teammate.ped));
        if (dist < bestDistance)
        {
            best = teammate.ped;
            bestDistance = dist;
        }
    }

    if (distanceOut)
        *distanceOut = bestDistance;
    return best;
}

float targetSelectionScore(const Fighter& fighter, Ped candidate, float distanceSq, DWORD t)
{
    if (!exists(candidate) ||
        (fighter.difficulty != Difficulty::Special && fighter.difficulty != Difficulty::Bosses))
    {
        return distanceSq;
    }

    bool current = candidate == fighter.currentTarget;
    bool canSee =
        PED::CAN_PED_IN_COMBAT_SEE_TARGET(fighter.ped, candidate) ||
        ENTITY::HAS_ENTITY_CLEAR_LOS_TO_ENTITY(fighter.ped, candidate, 17);
    if (fighter.difficulty == Difficulty::Special)
    {
        if (current && (canSee || distanceSq < 52.0f * 52.0f))
            return distanceSq * (canSee ? 0.52f : 0.72f);
        return canSee ? distanceSq * 0.82f : distanceSq;
    }

    bool recentlyHit = t - fighter.lastDamage < 1800u;
    bool longHunt = distanceSq > 64.0f * 64.0f;
    float score = distanceSq;
    bool mobileFireBoss = isMobileFireBoss(fighter);
    if (mobileFireBoss && current)
    {
        if (canSee && distanceSq < 80.0f * 80.0f)
            score *= 0.58f;
        else if (distanceSq < 55.0f * 55.0f)
            score *= 0.72f;
    }
    if (fighter.boss == kBossMicah)
    {
        if (!longHunt && distanceSq < 28.0f * 28.0f)
            score *= 0.45f;
        else if (!longHunt && distanceSq > 46.0f * 46.0f)
            score *= 1.18f;
        int candidateHealth = ENTITY::GET_ENTITY_HEALTH(candidate);
        if (!longHunt && candidateHealth > 0 && candidateHealth < 140)
            score *= 0.55f;
    }
    else if (fighter.boss == kBossDutch)
    {
        if (canSee && distanceSq > 34.0f * 34.0f)
            score *= longHunt ? 0.92f : 0.68f;
        else if (!longHunt && distanceSq < 16.0f * 16.0f)
            score *= 1.25f;
    }
    else if (fighter.boss == kBossColm && canSee)
    {
        score *= longHunt ? 0.92f : 0.72f;
    }
    if (mobileFireBoss && canSee)
    {
        int candidateHealth = ENTITY::GET_ENTITY_HEALTH(candidate);
        if (candidateHealth > 0 && candidateHealth < 130)
            score *= 0.62f;
    }

    score *= canSee ? (longHunt ? 0.92f : 0.62f) : (current ? 1.55f : 1.18f);
    if (current && canSee)
        score *= mobileFireBoss ? 0.90f : 0.68f;
    if (recentlyHit && !longHunt && canSee && distanceSq < 22.0f * 22.0f)
        score *= distanceSq < 9.0f * 9.0f ? 0.18f : 0.42f;
    return score;
}

Ped findClosestEnemy(const Fighter& fighter)
{
    if (!isAlive(fighter))
        return 0;

    Ped best{};
    float bestScore = 99999999.0f;
    DWORD t = GetTickCount();
    Vec3 origin = entityCoords(fighter.ped);
    Ped sharedTarget = sharedBattleRoyaleSquadTarget(fighter, origin);
    if (exists(sharedTarget))
    {
        best = sharedTarget;
        bestScore = targetSelectionScore(fighter, sharedTarget, distanceSquared(origin, entityCoords(sharedTarget)), t) * 0.58f;
    }

    if (!g_runtime.fighterSnapshots.empty())
    {
        ++g_runtime.targetScansUsingSnapshots;
        for (const FighterSnapshot& snapshot : g_runtime.fighterSnapshots)
        {
            if (!snapshot.targetable || snapshot.ped == fighter.ped || !exists(snapshot.ped))
                continue;

            bool sameTeamModeTeam = !freeForAllActive() && snapshot.team == fighter.team;
            bool sameBattleRoyaleSquad = freeForAllActive() && fighter.group && snapshot.group == fighter.group;
            if (sameTeamModeTeam || sameBattleRoyaleSquad)
                continue;

            float dist = distanceSquared(origin, snapshot.position);
            float score = targetSelectionScore(fighter, snapshot.ped, dist, t);
            if (score < bestScore)
            {
                best = snapshot.ped;
                bestScore = score;
            }
        }
    }
    else
    {
        ++g_runtime.targetScansWithoutSnapshots;
        for (const Fighter& other : g_runtime.fighters)
        {
            bool sameTeamModeTeam = !freeForAllActive() && other.team == fighter.team;
            bool sameBattleRoyaleSquad = freeForAllActive() && fighter.group && other.group == fighter.group;
            if (sameTeamModeTeam || sameBattleRoyaleSquad || other.ped == fighter.ped || !isAlive(other))
                continue;

            float dist = distanceSquared(origin, entityCoords(other.ped));
            float score = targetSelectionScore(fighter, other.ped, dist, t);
            if (score < bestScore)
            {
                best = other.ped;
                bestScore = score;
            }
        }
    }

    if (fighterRelationToPlayer(fighter) == PlayerRelation::Hostile)
    {
        Ped player = playerPed();
        if (exists(player) && !PED::IS_PED_DEAD_OR_DYING(player, true))
        {
            float dist = distanceSquared(origin, entityCoords(player));
            float score = targetSelectionScore(fighter, player, dist, t);
            if (score < bestScore)
            {
                best = player;
                bestScore = score;
            }
        }
    }

    return best;
}

bool isValidEnemyTarget(const Fighter& fighter, Ped candidate)
{
    if (!exists(candidate) || PED::IS_PED_DEAD_OR_DYING(candidate, true) || PED::IS_PED_FATALLY_INJURED(candidate))
        return false;

    if (candidate == playerPed())
        return playerAliveInBattle() && fighterRelationToPlayer(fighter) == PlayerRelation::Hostile;
    return true;
}

DWORD targetScanDelayForFighter(const Fighter& fighter)
{
    if (isMobileFireBoss(fighter))
        return 450u;
    if (fighter.difficulty == Difficulty::Bosses)
        return 650u;
    if (fighter.difficulty == Difficulty::Special)
        return 900u;
    return 0u;
}

bool shouldKeepCurrentTarget(const Fighter& fighter, DWORD t)
{
    if (!isMobileFireBoss(fighter) || !isValidEnemyTarget(fighter, fighter.currentTarget))
        return false;

    Vec3 self = entityCoords(fighter.ped);
    Vec3 targetPos = entityCoords(fighter.currentTarget);
    float dist = distanceSquared(self, targetPos);
    bool canSee =
        PED::CAN_PED_IN_COMBAT_SEE_TARGET(fighter.ped, fighter.currentTarget) ||
        ENTITY::HAS_ENTITY_CLEAR_LOS_TO_ENTITY(fighter.ped, fighter.currentTarget, 17);

    DWORD lockedFor = fighter.currentTargetStartedAt == 0 ? 0 : t - fighter.currentTargetStartedAt;
    if (lockedFor < 1700u && dist < 90.0f * 90.0f)
        return true;

    if (canSee && dist < 52.0f * 52.0f && lockedFor < 2900u && t - fighter.lastDamage > 700u)
        return true;

    if (canSee && dist < 24.0f * 24.0f && lockedFor < 3800u)
        return true;

    return false;
}

Ped closeHostilePlayerThreatTarget(Fighter& fighter, DWORD t)
{
    Ped player = playerPed();
    if (!isValidEnemyTarget(fighter, player))
        return 0;

    Vec3 self = entityCoords(fighter.ped);
    Vec3 playerPos = entityCoords(player);
    float playerDist = distanceSquared(self, playerPos);
    bool meleeBattle = g_menu.battleType != BattleType::AllWeapons;
    float interruptRange = meleeBattle ? 12.0f : 30.0f;
    float damagedRange = meleeBattle ? 18.0f : 46.0f;

    bool damagedByPlayer =
        (fighter.lastPlayerDamage != 0 && t - fighter.lastPlayerDamage < 2600u) ||
        ENTITY::HAS_ENTITY_BEEN_DAMAGED_BY_ENTITY(fighter.ped, player, true, true);
    if (damagedByPlayer)
        fighter.lastPlayerDamage = t;

    if (playerDist > damagedRange * damagedRange)
        return 0;

    bool canSeePlayer =
        PED::CAN_PED_IN_COMBAT_SEE_TARGET(fighter.ped, player) ||
        ENTITY::HAS_ENTITY_CLEAR_LOS_TO_ENTITY(fighter.ped, player, 17);

    if (damagedByPlayer && (canSeePlayer || playerDist <= interruptRange * interruptRange))
        return player;

    if (playerDist > interruptRange * interruptRange)
        return 0;

    if (fighter.currentTarget == player)
        return player;

    if (!isValidEnemyTarget(fighter, fighter.currentTarget))
        return player;

    float currentDist = distanceSquared(self, entityCoords(fighter.currentTarget));
    bool currentIsFar = currentDist > std::max(playerDist * 2.8f, (meleeBattle ? 18.0f : 42.0f) * (meleeBattle ? 18.0f : 42.0f));
    if (currentIsFar || canSeePlayer || playerDist <= (meleeBattle ? 6.0f : 14.0f) * (meleeBattle ? 6.0f : 14.0f))
        return player;

    return 0;
}

Ped selectCombatTarget(Fighter& fighter, DWORD t, bool force)
{
    Ped closePlayer = closeHostilePlayerThreatTarget(fighter, t);
    if (exists(closePlayer))
        return closePlayer;

    bool currentValid = isValidEnemyTarget(fighter, fighter.currentTarget);
    if (currentValid && !force && shouldKeepCurrentTarget(fighter, t))
        return fighter.currentTarget;

    DWORD scanDelay = targetScanDelayForFighter(fighter);
    if (currentValid && !force && (scanDelay == 0u || t - fighter.lastTargetScan < scanDelay))
        return fighter.currentTarget;

    if (deathmatchActive())
        ++g_runtime.deathmatchRetargetsRequested;

    if (deathmatchActive() &&
        !force &&
        !isEnhancedFighter(fighter) &&
        g_runtime.fullRetargetsThisFrame >= g_settings.deathmatchMaximumFullRetargetsPerFrame)
    {
        fighter.lastTargetScan = t;
        ++g_runtime.deathmatchRetargetsDeferred;
        return currentValid ? fighter.currentTarget : 0;
    }

    if (deathmatchActive())
    {
        ++g_runtime.fullRetargetsThisFrame;
        ++g_runtime.deathmatchRetargetsProcessed;
    }

    fighter.lastTargetScan = t;
    return findClosestEnemy(fighter);
}

bool redirectFriendlyAwayFromPlayer(Fighter& fighter, DWORD t)
{
    if (!isAlive(fighter))
    {
        return false;
    }

    if (freeForAllActive())
    {
        if (!isPlayerBattleRoyaleSquadmate(fighter))
            return false;
    }
    else if (fighter.team < 0 ||
        fighter.team >= kTeamCount ||
        runtimeRelationToPlayer(fighter.team) != PlayerRelation::Friendly)
    {
        return false;
    }

    Ped player = playerPed();
    if (!exists(player))
        return false;

    bool targetingPlayer =
        PED::IS_PED_IN_COMBAT(fighter.ped, player) ||
        PED::GET_MELEE_TARGET_FOR_PED(fighter.ped) == player;
    if (!targetingPlayer)
        return false;

    AI::CLEAR_PED_TASKS_IMMEDIATELY(fighter.ped, true, false);
    PED::SET_PED_RELATIONSHIP_GROUP_DEFAULT_HASH(fighter.ped, fighter.group);
    PED::SET_PED_RELATIONSHIP_GROUP_HASH(fighter.ped, fighter.group);
    applyDamagePermissions(fighter);
    ENTITY::CLEAR_ENTITY_LAST_DAMAGE_ENTITY(fighter.ped);
    PED::CLEAR_PED_LAST_DAMAGE_BONE(fighter.ped);
    fighter.currentTarget = 0;
    fighter.currentTargetStartedAt = 0;
    fighter.lastTask = 0;
    fighter.lastDamage = t;

    Ped target = findClosestEnemy(fighter);
    if (exists(target))
    {
        PED::REGISTER_TARGET(fighter.ped, target, true);
        AI::TASK_COMBAT_PED(fighter.ped, target, 0, 16);
        if (fighter.currentTarget != target)
            fighter.currentTargetStartedAt = t;
        fighter.currentTarget = target;
        fighter.lastTask = t;
    }

    return true;
}

void readyWeapon(Fighter& fighter, DWORD t, bool force = false)
{
    if (!isAlive(fighter) || !fighter.combatWeapon)
        return;

    if (weaponControllerActive(fighter) && isNormalWeaponForFighter(fighter, fighter.combatWeapon))
    {
        requestManagedWeapon(fighter, fighter.combatWeapon, t, force, force ? "force-ready" : "ready");
        return;
    }

    if (!force && t - fighter.lastWeaponReady < 1400)
        return;

    ensureWeaponHash(fighter.ped, fighter.combatWeapon, false);
    fillWeaponAmmo(fighter.ped, fighter.combatWeapon);

    Hash current{};
    bool alreadyEquipped =
        WEAPON::GET_CURRENT_PED_WEAPON(fighter.ped, &current, true, 0, false) &&
        current == fighter.combatWeapon;

    if (isMobileFireBoss(fighter) &&
        force &&
        fighter.lastWeaponReadyHash == fighter.combatWeapon &&
        alreadyEquipped)
    {
        return;
    }

    bool micahDual =
        fighter.difficulty == Difficulty::Bosses &&
        fighter.boss == kBossMicah;
    if (micahDual && current == joaat("WEAPON_REVOLVER_DOUBLEACTION"))
        alreadyEquipped = true;

    if (micahDual)
    {
        if (!alreadyEquipped || t - fighter.lastWeaponReady > 2400)
            equipMicahDualRevolvers(fighter.ped, fighter.combatWeapon, false);
    }
    else if (!alreadyEquipped)
    {
        WEAPON::SET_CURRENT_PED_WEAPON(fighter.ped, fighter.combatWeapon, true, 0, false, false);
    }
    else
    {
        fighter.lastWeaponReady = t;
        fighter.lastWeaponReadyHash = fighter.combatWeapon;
        return;
    }

    fighter.lastWeaponReady = t;
    fighter.lastWeaponReadyHash = fighter.combatWeapon;
}

void restoreFighterWeapons(Fighter& fighter, DWORD t, bool equip)
{
    if (!exists(fighter.ped))
        return;

    if (g_menu.battleType == BattleType::NoWeapons)
    {
        resetWeaponController(fighter);
        WEAPON::REMOVE_ALL_PED_WEAPONS(fighter.ped, true, true);
        fighter.combatWeapon = joaat("WEAPON_UNARMED");
        WEAPON::SET_CURRENT_PED_WEAPON(fighter.ped, fighter.combatWeapon, true, 0, false, false);
        fighter.lastWeaponReady = t;
        fighter.lastWeaponReadyHash = fighter.combatWeapon;
        return;
    }

    ensureWeaponHash(fighter.ped, fighter.closeWeapon, false);
    ensureWeaponHash(fighter.ped, fighter.mediumWeapon, false);
    ensureWeaponHash(fighter.ped, fighter.longWeapon, false);
    ensureWeaponHash(fighter.ped, fighter.combatWeapon, false);

    Hash desired = fighter.combatWeapon;
    if (isUnarmedWeapon(desired))
        desired = fighter.mediumWeapon ? fighter.mediumWeapon : (fighter.longWeapon ? fighter.longWeapon : fighter.closeWeapon);
    if (isUnarmedWeapon(desired))
        desired = currentOrBestPedWeapon(fighter.ped);
    if (isUnarmedWeapon(desired))
        return;

    fighter.combatWeapon = desired;
    if (equip)
        readyWeapon(fighter, t, true);
    else
        fillWeaponAmmo(fighter.ped, fighter.combatWeapon);
}

bool isAdvancedFighter(const Fighter& fighter)
{
    return fighter.difficulty == Difficulty::Special ||
        fighter.difficulty == Difficulty::Bosses;
}

bool isEnhancedFighter(const Fighter& fighter)
{
    return fighter.difficulty == Difficulty::Special ||
        fighter.difficulty == Difficulty::Bosses;
}

int projectileAmmo(Ped ped, Hash weapon)
{
    if (!exists(ped) || isUnarmedWeapon(weapon) || !WEAPON::HAS_PED_GOT_WEAPON(ped, weapon, false, false))
        return 0;

    return WEAPON::GET_AMMO_IN_PED_WEAPON(ped, weapon);
}

bool projectileAmmoDecreased(const Fighter& fighter)
{
    if (fighter.projectileAmmoBefore < 0 || !exists(fighter.ped) || isUnarmedWeapon(fighter.projectileWeapon))
        return false;

    return projectileAmmo(fighter.ped, fighter.projectileWeapon) < fighter.projectileAmmoBefore;
}

int projectileTaskStatus(Ped ped)
{
    if (!exists(ped) || kTaskHashThrowProjectile == 0)
        return -1;

    return AI::GET_SCRIPT_TASK_STATUS(ped, kTaskHashThrowProjectile, true);
}

bool projectileTaskStillActive(int status)
{
    return status >= 0 && status <= 6;
}

Hash projectileRestoreWeaponForFighter(const Fighter& fighter)
{
    Hash current = currentNormalWeapon(fighter);
    if (current)
        return current;

    if (isNormalWeaponForFighter(fighter, fighter.confirmedWeapon))
        return fighter.confirmedWeapon;

    if (isNormalWeaponForFighter(fighter, fighter.combatWeapon))
        return fighter.combatWeapon;

    if (!isUnarmedWeapon(fighter.mediumWeapon))
        return fighter.mediumWeapon;
    if (!isUnarmedWeapon(fighter.longWeapon))
        return fighter.longWeapon;
    if (!isUnarmedWeapon(fighter.closeWeapon))
        return fighter.closeWeapon;

    return fighter.combatWeapon;
}

bool restoreProjectileWeapon(Fighter& fighter, DWORD t)
{
    Hash restoreWeapon = projectileRestoreWeaponForFighter(fighter);
    if (!isUnarmedWeapon(fighter.projectileRestoreWeapon))
        restoreWeapon = fighter.projectileRestoreWeapon;

    clearTemporaryWeaponOverride(fighter);
    fighter.weaponPending = 0;
    fighter.weaponPendingSince = 0;
    fighter.weaponRetryCount = 0;
    fighter.weaponSettleUntil = 0;

    if (isUnarmedWeapon(restoreWeapon))
    {
        resetScriptedActionState(fighter, true);
        return false;
    }

    fighter.combatWeapon = restoreWeapon;
    if (weaponControllerActive(fighter) && isNormalWeaponForFighter(fighter, restoreWeapon))
    {
        requestManagedWeapon(fighter, restoreWeapon, t, true, "projectile-restore");
        confirmManagedWeaponIfEquipped(fighter, t);
        if (currentNormalWeapon(fighter) == restoreWeapon && !weaponControllerSettling(fighter, t))
        {
            resetScriptedActionState(fighter, false);
            return false;
        }
        return true;
    }

    readyWeapon(fighter, t, true);
    resetScriptedActionState(fighter, false);
    return false;
}

void issueProjectileThrowTask(Fighter& fighter, DWORD t, bool retry)
{
    if (!exists(fighter.ped) || isUnarmedWeapon(fighter.projectileWeapon))
        return;

    if (!retry)
        fighter.projectileAmmoBefore = projectileAmmo(fighter.ped, fighter.projectileWeapon);

    AI::CLEAR_PED_TASKS(fighter.ped, true, false);
    if (exists(fighter.projectileTarget))
        PED::REGISTER_TARGET(fighter.ped, fighter.projectileTarget, true);

    AI::TASK_THROW_PROJECTILE(
        fighter.ped,
        fighter.projectileThrowPos.x,
        fighter.projectileThrowPos.y,
        fighter.projectileThrowPos.z);

    fighter.projectileTaskIssued = true;
    fighter.projectileTaskRequestedAt = t;
    fighter.projectileCommittedAt = retry ? fighter.projectileCommittedAt : t;
    fighter.scriptedActionTimeoutAt = t + kProjectileHardTimeoutMs;
    fighter.dynamitePhase = DynamitePhase::ThrowActive;
    fighter.lastTask = t;
    debugActionState(fighter, retry ? "projectile-retry" : "projectile-throw-issued");
}

bool startProjectileThrowAction(
    Fighter& fighter,
    Ped target,
    DWORD t,
    Hash weapon,
    Vec3 throwPos,
    Hash restoreWeapon,
    int ammo,
    const char* debugName)
{
    if (!exists(fighter.ped) ||
        isUnarmedWeapon(weapon) ||
        protectedScriptedActionActive(fighter) ||
        t < fighter.projectileFailureCooldownUntil)
    {
        return false;
    }

    fighter.scriptedActionType = ScriptedActionType::DynamiteThrow;
    fighter.dynamitePhase = DynamitePhase::Equipping;
    fighter.scriptedActionStartedAt = t;
    fighter.scriptedActionResumeAt = t + kProjectileHardTimeoutMs + 1800u;
    fighter.scriptedActionTimeoutAt = t + kProjectileHardTimeoutMs + 2500u;
    fighter.projectileWeapon = weapon;
    fighter.projectileRestoreWeapon = restoreWeapon;
    fighter.projectileTarget = target;
    fighter.projectileThrowPos = throwPos;
    fighter.projectileAmmoBefore = -1;
    fighter.projectileTaskIssued = false;
    fighter.projectileTaskObservedActive = false;
    fighter.projectileReleaseConfirmed = false;
    fighter.projectileTaskRetries = 0;
    fighter.projectileEquipRequestedAt = 0;
    fighter.projectileTaskRequestedAt = 0;
    fighter.projectileCommittedAt = 0;
    fighter.currentTarget = target;
    fighter.currentTargetStartedAt = t;

    beginTemporaryWeaponOverride(fighter, weapon, t, kProjectileHardTimeoutMs + 3000u);
    requestTemporaryWeaponEquip(fighter, weapon, t, ammo, debugName);
    fighter.projectileEquipRequestedAt = t;
    debugActionState(fighter, "projectile-eligible");
    return true;
}

bool maintainDynamiteThrow(Fighter& fighter, DWORD t)
{
    if (!projectileActionActive(fighter))
        return false;

    bool dead =
        !exists(fighter.ped) ||
        PED::IS_PED_DEAD_OR_DYING(fighter.ped, true) ||
        PED::IS_PED_FATALLY_INJURED(fighter.ped);
    if (dead)
    {
        resetScriptedActionState(fighter, true);
        return false;
    }

    extendTemporaryWeaponOverride(fighter, fighter.projectileWeapon, t, 1500u);

    bool committed = fighter.dynamitePhase == DynamitePhase::ThrowActive ||
        fighter.dynamitePhase == DynamitePhase::Recovering ||
        fighter.projectileCommittedAt != 0;
    if (!committed &&
        fighter.projectileTarget != 0 &&
        !isValidEnemyTarget(fighter, fighter.projectileTarget))
    {
        fighter.projectileFailureCooldownUntil = t + kProjectileFailureCooldownMs;
        debugActionState(fighter, "projectile-target-lost-before-commit");
        return restoreProjectileWeapon(fighter, t);
    }

    if (t > fighter.scriptedActionTimeoutAt && fighter.dynamitePhase != DynamitePhase::Recovering)
    {
        if (projectileAmmoDecreased(fighter))
        {
            fighter.projectileReleaseConfirmed = true;
            fighter.dynamitePhase = DynamitePhase::Recovering;
        }
        else
        {
            fighter.projectileFailureCooldownUntil = t + kProjectileFailureCooldownMs;
            fighter.dynamitePhase = DynamitePhase::Recovering;
            debugActionState(fighter, "projectile-timeout");
        }
    }

    switch (fighter.dynamitePhase)
    {
    case DynamitePhase::Equipping:
    {
        bool equipped = requestTemporaryWeaponEquip(fighter, fighter.projectileWeapon, t, 3, "projectile-equip");
        if (!equipped)
            return true;

        fighter.dynamitePhase = DynamitePhase::ThrowRequested;
        fighter.scriptedActionStartedAt = t;
        fighter.scriptedActionResumeAt = t + kProjectileHardTimeoutMs;
        debugActionState(fighter, "projectile-equip-confirmed");
        return true;
    }
    case DynamitePhase::ThrowRequested:
    {
        Hash current = currentManagedWeapon(fighter);
        if (current != fighter.projectileWeapon)
        {
            fighter.dynamitePhase = DynamitePhase::Equipping;
            return true;
        }

        if (weaponControllerSettling(fighter, t) || t - fighter.scriptedActionStartedAt < 100u)
            return true;

        issueProjectileThrowTask(fighter, t, false);
        if (fighter.projectileWeapon == joaat("WEAPON_THROWN_DYNAMITE"))
            fighter.lastDynamiteTask = t;
        return true;
    }
    case DynamitePhase::ThrowActive:
    {
        int status = -1;
        if (kTaskHashThrowProjectile != 0)
            status = projectileTaskStatus(fighter.ped);
        if (kTaskHashThrowProjectile != 0 && projectileTaskStillActive(status))
            fighter.projectileTaskObservedActive = true;

        bool ammoDropped = projectileAmmoDecreased(fighter);
        bool taskFinished = kTaskHashThrowProjectile != 0 &&
            (status == 8 ||
             (fighter.projectileTaskObservedActive && status == 7 && t - fighter.projectileTaskRequestedAt > kProjectileStartGraceMs));
        if (ammoDropped || taskFinished)
        {
            fighter.projectileReleaseConfirmed = true;
            fighter.dynamitePhase = DynamitePhase::Recovering;
            debugActionState(fighter, ammoDropped ? "projectile-ammo-confirmed" : "projectile-task-finished");
            return true;
        }

        bool canRetry =
            fighter.projectileTaskRetries < 1 &&
            currentManagedWeapon(fighter) == fighter.projectileWeapon &&
            !fighter.projectileTaskObservedActive &&
            t - fighter.projectileTaskRequestedAt > kProjectileRetryDelayMs &&
            t - fighter.projectileCommittedAt < kProjectileHardTimeoutMs - 1200u;
        if (canRetry)
        {
            ++fighter.projectileTaskRetries;
            issueProjectileThrowTask(fighter, t, true);
        }
        return true;
    }
    case DynamitePhase::Recovering:
        return restoreProjectileWeapon(fighter, t);
    case DynamitePhase::None:
    default:
        resetScriptedActionState(fighter, true);
        return false;
    }
}

void scheduleScriptedCombatResume(Fighter& fighter, DWORD t, DWORD delayMs)
{
    if (fighter.difficulty != Difficulty::Bosses && fighter.difficulty != Difficulty::Special)
        return;

    if (protectedScriptedActionActive(fighter))
        return;

    fighter.scriptedActionType = ScriptedActionType::Other;
    fighter.scriptedActionStartedAt = t;
    fighter.scriptedActionResumeAt = t + std::max<DWORD>(250u, delayMs);
    fighter.scriptedActionTimeoutAt = fighter.scriptedActionResumeAt + 2500u;
}

bool maintainScriptedCombatAction(Fighter& fighter, Ped target, DWORD t)
{
    if (fighter.scriptedActionType == ScriptedActionType::None && fighter.scriptedActionResumeAt == 0)
        return false;

    if (fighter.scriptedActionType == ScriptedActionType::DynamiteThrow)
        return maintainDynamiteThrow(fighter, t);

    if (fighter.scriptedActionType == ScriptedActionType::BossEvasion)
    {
        if (!exists(fighter.ped) ||
            PED::IS_PED_DEAD_OR_DYING(fighter.ped, true) ||
            PED::IS_PED_FATALLY_INJURED(fighter.ped))
        {
            resetScriptedActionState(fighter, true);
            return false;
        }

        if (PED::IS_PED_SHOOTING(fighter.ped))
            fighter.evasionShotsObserved = true;

        Ped actionTarget = isValidEnemyTarget(fighter, fighter.evasionFiringTarget) ?
            fighter.evasionFiringTarget :
            (isValidEnemyTarget(fighter, target) ? target : fighter.evasionAimTarget);

        if (exists(actionTarget))
        {
            if (fighter.evasionShootDuringDash && isValidEnemyTarget(fighter, actionTarget))
                PED::REGISTER_TARGET(fighter.ped, actionTarget, true);
            PED::SET_PED_SHOOT_RATE(fighter.ped, bossShootRate(fighter));
        }

        if (!updateBossEvasionStart(fighter, t))
        {
            recoverFromBossEvasion(fighter, t);
            return true;
        }

        if (t < fighter.scriptedActionResumeAt)
            return true;

        recoverFromBossEvasion(fighter, t);
        return true;
    }

    if (!exists(target) || PED::IS_PED_DEAD_OR_DYING(target, true) || PED::IS_PED_FATALLY_INJURED(target))
    {
        resetScriptedActionState(fighter, false);
        return false;
    }

    bool shooting = PED::IS_PED_SHOOTING(fighter.ped) != 0;
    bool reloading = PED::IS_PED_RELOADING(fighter.ped) != 0;
    bool moving =
        AI::IS_PED_WALKING(fighter.ped) ||
        AI::IS_PED_RUNNING(fighter.ped) ||
        AI::IS_PED_SPRINTING(fighter.ped) ||
        PED::IS_PED_GOING_INTO_COVER(fighter.ped);
    bool settling = t - fighter.scriptedActionStartedAt < 650u;
    if (t < fighter.scriptedActionResumeAt && (settling || shooting || reloading || moving))
        return true;

    if ((shooting || reloading) && t >= fighter.scriptedActionResumeAt)
    {
        fighter.scriptedActionResumeAt = t + 250u;
        return true;
    }

    if (shouldPollManagedWeapon(fighter, t))
        confirmManagedWeaponIfEquipped(fighter, t);
    bool underSustainedFire =
        fighter.recentDamageHits >= 2 &&
        fighter.recentDamageWindowStarted != 0 &&
        t - fighter.recentDamageWindowStarted <= 4500u;
    if (weaponControllerSettling(fighter, t) && !underSustainedFire)
        return true;

    bool forceWeapon = isMobileFireBoss(fighter) && !weaponControllerActive(fighter);
    readyWeapon(fighter, t, forceWeapon);
    PED::REGISTER_TARGET(fighter.ped, target, true);
    AI::TASK_COMBAT_PED(fighter.ped, target, 0, 16);
    if (fighter.currentTarget != target)
        fighter.currentTargetStartedAt = t;
    fighter.currentTarget = target;
    fighter.lastTask = t;
    resetScriptedActionState(fighter, false);
    return true;
}

bool isLowHealthBoss(const Fighter& fighter, int health)
{
    return fighter.difficulty == Difficulty::Bosses &&
        health > 0 &&
        health < g_settings.bossDefensiveHealthThreshold;
}

DWORD combatRetaskDelay(const Fighter& fighter)
{
    if (fighter.difficulty == Difficulty::Special)
        return kSpecialPeds[static_cast<size_t>(fighter.special)].retaskDelayMs;
    if (fighter.difficulty == Difficulty::Bosses)
        return kBosses[static_cast<size_t>(fighter.boss)].retaskDelayMs;

    switch (fighter.difficulty)
    {
    case Difficulty::Easy:
    case Difficulty::Medium:
    case Difficulty::Hard:
    case Difficulty::Extreme:
    case Difficulty::Special:
    case Difficulty::Bosses:
        return kDifficulty[static_cast<size_t>(difficultyIndex(fighter.difficulty))].retaskDelayMs;
    }
    return kDifficulty[static_cast<size_t>(difficultyIndex(fighter.difficulty))].retaskDelayMs;
}

DWORD shootBurstDelay(const Fighter& fighter)
{
    if (fighter.difficulty == Difficulty::Special)
        return kSpecialPeds[static_cast<size_t>(fighter.special)].shootBurstDelayMs;
    if (fighter.difficulty == Difficulty::Bosses)
        return kBosses[static_cast<size_t>(fighter.boss)].shootBurstDelayMs;

    switch (fighter.difficulty)
    {
    case Difficulty::Easy:
    case Difficulty::Medium:
    case Difficulty::Hard:
    case Difficulty::Extreme:
    case Difficulty::Special:
    case Difficulty::Bosses:
        return kDifficulty[static_cast<size_t>(difficultyIndex(fighter.difficulty))].shootBurstDelayMs;
    }
    return kDifficulty[static_cast<size_t>(difficultyIndex(fighter.difficulty))].shootBurstDelayMs;
}

bool isFightingTeammate(const Fighter& fighter)
{
    if (!isAlive(fighter))
        return false;

    Ped meleeTarget = PED::GET_MELEE_TARGET_FOR_PED(fighter.ped);
    for (const Fighter& other : g_runtime.fighters)
    {
        bool teammate = freeForAllActive() ?
            (fighter.group && other.group == fighter.group) :
            (other.team == fighter.team);

        if (!teammate || other.ped == fighter.ped || !isAlive(other))
            continue;

        if (PED::IS_PED_IN_COMBAT(fighter.ped, other.ped))
            return true;

        if (meleeTarget == other.ped)
            return true;
    }

    return false;
}

bool taskPursueDistantTarget(Fighter& fighter, Ped target, DWORD t, float dist, bool force)
{
    if (!isEnhancedFighter(fighter) || !exists(target))
        return false;

    if (taskConvergeTowardDistantTarget(fighter, target, t, dist, force))
        return true;

    bool meleeBattle = g_menu.battleType != BattleType::AllWeapons;
    float preferredRange = meleeBattle ? 5.0f : preferredGunRangeForFighter(fighter);
    float huntStart = meleeBattle ? 20.0f : std::max(54.0f, preferredRange + 32.0f);
    if (dist < huntStart * huntStart)
        return false;

    DWORD refreshDelay = meleeBattle ? 1450u : (dist > 120.0f * 120.0f ? 2600u : 3200u);
    if (!meleeBattle && isAdvancedFighter(fighter))
        refreshDelay = dist > 120.0f * 120.0f ? 2200u : 2700u;
    if (!force && t - fighter.lastRepositionTask < refreshDelay)
        return true;

    float stopRange = meleeBattle ? 3.0f : std::max(14.0f, preferredRange * 0.72f);
    float speed = combatMoveSpeedForFighter(fighter);

    readyWeapon(fighter, t, force);
    PED::REGISTER_TARGET(fighter.ped, target, true);
    AI::TASK_GO_TO_ENTITY(
        fighter.ped,
        target,
        meleeBattle ? 6200 : 18000,
        stopRange,
        speed,
        0.0f,
        0);

    if (fighter.currentTarget != target)
        fighter.currentTargetStartedAt = t;
    fighter.currentTarget = target;
    fighter.lastRepositionTask = t;
    fighter.lastTask = t;
    return true;
}

bool taskConvergeTowardDistantTarget(Fighter& fighter, Ped target, DWORD t, float distSq, bool force)
{
    if (!exists(target))
        return false;

    bool meleeBattle = g_menu.battleType != BattleType::AllWeapons;
    float preferredRange = meleeBattle ? 4.5f : preferredGunRangeForFighter(fighter);
    bool enhanced = isEnhancedFighter(fighter);
    float triggerRange = meleeBattle ? 30.0f : (enhanced ? std::max(76.0f, preferredRange + 30.0f) : 68.0f);
    if (distSq < triggerRange * triggerRange)
        return false;

    DWORD refreshDelay = distSq > 150.0f * 150.0f ? 1450u : 1850u;
    if (enhanced)
        refreshDelay = distSq > 150.0f * 150.0f ? 1200u : 1550u;
    if (!force && t - fighter.lastRepositionTask < refreshDelay)
        return true;

    Vec3 self = entityCoords(fighter.ped);
    Vec3 targetPos = entityCoords(target);
    float dx = targetPos.x - self.x;
    float dy = targetPos.y - self.y;
    float planarDist = std::sqrt(std::max(0.001f, dx * dx + dy * dy));
    if (planarDist < triggerRange)
        return false;

    float stopRange = meleeBattle ? 4.0f : std::max(10.0f, preferredRange * 0.72f);
    float step = std::clamp(planarDist - stopRange, 34.0f, enhanced ? 92.0f : 76.0f);
    Vec3 moveTo{
        self.x + (dx / planarDist) * step,
        self.y + (dy / planarDist) * step,
        self.z
    };
    snapToGround(moveTo);

    STREAMING::REQUEST_COLLISION_AT_COORD(moveTo.x, moveTo.y, moveTo.z);
    PATHFIND::ADD_NAVMESH_REQUIRED_REGION(moveTo.x, moveTo.y, 14.0f);
    if (g_menu.battleType == BattleType::AllWeapons)
        readyWeapon(fighter, t, force);
    PED::REGISTER_TARGET(fighter.ped, target, true);
    AI::SET_PED_DESIRED_MOVE_BLEND_RATIO(fighter.ped, combatMoveSpeedForFighter(fighter));
    AI::TASK_FOLLOW_NAV_MESH_TO_COORD(
        fighter.ped,
        moveTo.x,
        moveTo.y,
        moveTo.z,
        combatMoveSpeedForFighter(fighter),
        18000,
        meleeBattle ? 1.8f : 3.0f,
        true,
        headingToward(self, targetPos));

    if (fighter.currentTarget != target)
        fighter.currentTargetStartedAt = t;
    fighter.currentTarget = target;
    fighter.lastRepositionTask = t;
    fighter.lastTask = t;
    fighter.lastObservedMovementAt = t;
    fighter.lastCombatActivityAt = t;
    return true;
}

bool taskApproachTarget(Fighter& fighter, Ped target, DWORD t, bool force, bool canSeeTarget = true)
{
    if (!exists(target))
        return false;

    float preferredRange = preferredGunRangeForFighter(fighter);
    DWORD delay = approachDelayForFighter(fighter);
    if (!force && t - fighter.lastRepositionTask < delay)
        return false;

    float dist = distanceSquared(entityCoords(fighter.ped), entityCoords(target));
    readyWeapon(fighter, t, force);
    PED::REGISTER_TARGET(fighter.ped, target, true);
    float stopRange = std::max(8.0f, preferredRange * 0.68f);
    bool shootWhileMoving = isAdvancedFighter(fighter);
    bool runFirst = !canSeeTarget || dist > (preferredRange + 10.0f) * (preferredRange + 10.0f);
    if (runFirst)
    {
        AI::TASK_GO_TO_ENTITY(
            fighter.ped,
            target,
            14000,
            stopRange,
            combatMoveSpeedForFighter(fighter),
            0.0f,
            0);
    }
    else
    {
        AI::TASK_GO_TO_ENTITY_WHILE_AIMING_AT_ENTITY(
            fighter.ped,
            target,
            target,
            combatMoveSpeedForFighter(fighter),
            shootWhileMoving,
            stopRange,
            preferredRange,
            true,
            false,
            joaat("FIRING_PATTERN_FULL_AUTO"),
            0);
    }
    fighter.lastRepositionTask = t;
    fighter.lastTask = t;
    scheduleScriptedCombatResume(fighter, t, 2200u);
    return true;
}

bool taskOrdinaryAdvanceIfDistant(Fighter& fighter, Ped target, DWORD t, float dist, bool force, bool canSeeTarget)
{
    if (taskConvergeTowardDistantTarget(fighter, target, t, dist, force))
        return true;

    if (isEnhancedFighter(fighter) ||
        g_menu.battleType != BattleType::AllWeapons ||
        !exists(target))
    {
        return false;
    }

    float preferredRange = preferredGunRangeForFighter(fighter);
    float extraRange = 8.0f;
    if (fighter.difficulty == Difficulty::Hard)
        extraRange = 10.0f;
    else if (fighter.difficulty == Difficulty::Extreme)
        extraRange = 12.0f;

    float triggerRange = preferredRange + extraRange;
    if (dist <= triggerRange * triggerRange)
        return false;

    DWORD delay = std::max<DWORD>(950u, approachDelayForFighter(fighter) / 2);
    if (!force && t - fighter.lastRepositionTask < delay)
        return true;

    float stopRange = std::max(6.0f, preferredRange * 0.72f);
    bool shootWhileMoving =
        canSeeTarget &&
        (fighter.difficulty == Difficulty::Hard || fighter.difficulty == Difficulty::Extreme);

    readyWeapon(fighter, t, force);
    PED::REGISTER_TARGET(fighter.ped, target, true);
    if (shootWhileMoving)
    {
        AI::TASK_GO_TO_ENTITY_WHILE_AIMING_AT_ENTITY(
            fighter.ped,
            target,
            target,
            combatMoveSpeedForFighter(fighter),
            true,
            stopRange,
            preferredRange,
            true,
            false,
            joaat("FIRING_PATTERN_FULL_AUTO"),
            0);
    }
    else
    {
        AI::TASK_GO_TO_ENTITY(
            fighter.ped,
            target,
            9000,
            stopRange,
            combatMoveSpeedForFighter(fighter),
            0.0f,
            0);
    }

    fighter.lastRepositionTask = t;
    fighter.lastTask = t;
    return true;
}

int ordinaryCombatMoveChance(const Fighter& fighter)
{
    switch (fighter.difficulty)
    {
    case Difficulty::Easy:
        return 10;
    case Difficulty::Medium:
        return 16;
    case Difficulty::Hard:
        return 24;
    case Difficulty::Extreme:
        return 34;
    default:
        return 0;
    }
}

DWORD ordinaryCombatMoveDelay(const Fighter& fighter)
{
    switch (fighter.difficulty)
    {
    case Difficulty::Easy:
        return 5600u;
    case Difficulty::Medium:
        return 4700u;
    case Difficulty::Hard:
        return 3600u;
    case Difficulty::Extreme:
        return 2800u;
    default:
        return 5000u;
    }
}

bool taskOrdinaryCombatMovementNudge(Fighter& fighter, Ped target, DWORD t, float dist, bool canSeeTarget)
{
    if (isEnhancedFighter(fighter) ||
        g_menu.battleType != BattleType::AllWeapons ||
        !exists(target) ||
        !canSeeTarget ||
        PED::IS_PED_IN_COVER(fighter.ped, false, false) ||
        PED::IS_PED_AIMING_FROM_COVER(fighter.ped) ||
        PED::IS_PED_GOING_INTO_COVER(fighter.ped) ||
        t - fighter.lastRepositionTask < ordinaryCombatMoveDelay(fighter))
    {
        return false;
    }

    float preferredRange = preferredGunRangeForFighter(fighter);
    if (dist < 9.0f * 9.0f || dist > (preferredRange + 18.0f) * (preferredRange + 18.0f))
        return false;

    if (randomRange(1, 100) > ordinaryCombatMoveChance(fighter))
        return false;

    Vec3 self = entityCoords(fighter.ped);
    Vec3 targetPos = entityCoords(target);
    float dx = targetPos.x - self.x;
    float dy = targetPos.y - self.y;
    float len = std::sqrt(std::max(0.001f, dx * dx + dy * dy));
    float sideSign = randomRange(0, 1) == 0 ? -1.0f : 1.0f;
    float sideX = (-dy / len) * sideSign;
    float sideY = (dx / len) * sideSign;
    float forwardX = dx / len;
    float forwardY = dy / len;
    float sideDistance = 2.2f;
    float forwardDistance = 0.0f;

    switch (fighter.difficulty)
    {
    case Difficulty::Easy:
        sideDistance = 1.8f;
        forwardDistance = dist > preferredRange * preferredRange ? 1.6f : -0.6f;
        break;
    case Difficulty::Medium:
        sideDistance = 2.4f;
        forwardDistance = dist > preferredRange * preferredRange ? 2.2f : -0.8f;
        break;
    case Difficulty::Hard:
        sideDistance = 3.2f;
        forwardDistance = dist > preferredRange * preferredRange ? 3.0f : -1.0f;
        break;
    case Difficulty::Extreme:
        sideDistance = 4.2f;
        forwardDistance = dist > preferredRange * preferredRange ? 3.6f : -1.2f;
        break;
    default:
        break;
    }

    Vec3 moveTo{
        self.x + sideX * sideDistance + forwardX * forwardDistance,
        self.y + sideY * sideDistance + forwardY * forwardDistance,
        self.z
    };
    snapToGround(moveTo);

    readyWeapon(fighter, t, false);
    PED::REGISTER_TARGET(fighter.ped, target, true);
    AI::TASK_GO_TO_COORD_WHILE_AIMING_AT_ENTITY(
        fighter.ped,
        moveTo.x,
        moveTo.y,
        moveTo.z,
        target,
        std::min(3.25f, combatMoveSpeedForFighter(fighter)),
        true,
        1.0f,
        2.4f,
        true,
        0,
        true,
        joaat("FIRING_PATTERN_FULL_AUTO"),
        0,
        0);
    fighter.lastRepositionTask = t;
    fighter.lastTask = t;
    fighter.lastObservedMovementAt = t;
    fighter.lastCombatActivityAt = t;
    return true;
}

bool taskStrafeTarget(Fighter& fighter, Ped target, DWORD t, float dist, bool canSeeTarget)
{
    bool eliteDuel = eliteNpcDuelTarget(fighter, target);
    DWORD repositionDelay = fighter.difficulty == Difficulty::Bosses ? 1900u : (eliteDuel ? 1800u : 2800u);
    float maxStrafeDistance = eliteDuel ? 72.0f : 58.0f;
    if (!isAdvancedFighter(fighter) ||
        !exists(target) ||
        !canSeeTarget ||
        t - fighter.lastRepositionTask < repositionDelay ||
        dist < 10.0f * 10.0f ||
        dist > maxStrafeDistance * maxStrafeDistance)
    {
        return false;
    }

    Vec3 self = entityCoords(fighter.ped);
    Vec3 targetPos = entityCoords(target);
    float dx = targetPos.x - self.x;
    float dy = targetPos.y - self.y;
    float len = std::sqrt(std::max(0.001f, dx * dx + dy * dy));
    float sideSign = randomRange(0, 1) == 0 ? -1.0f : 1.0f;
    float sideX = (-dy / len) * sideSign;
    float sideY = (dx / len) * sideSign;
    float forwardX = dx / len;
    float forwardY = dy / len;
    float sideDistance = fighter.difficulty == Difficulty::Bosses ? (eliteDuel ? 13.0f : 11.0f) : (eliteDuel ? 11.5f : 8.0f);
    float forwardDistance = dist > preferredGunRangeForFighter(fighter) * preferredGunRangeForFighter(fighter) ? 6.0f : -2.0f;

    Vec3 moveTo{
        self.x + sideX * sideDistance + forwardX * forwardDistance,
        self.y + sideY * sideDistance + forwardY * forwardDistance,
        self.z
    };
    snapToGround(moveTo);

    if (weaponControllerActive(fighter) && isNormalWeaponForFighter(fighter, fighter.combatWeapon))
    {
        Hash current = currentNormalWeapon(fighter);
        if (current)
            fighter.combatWeapon = current;
        fillWeaponAmmo(fighter.ped, fighter.combatWeapon);
    }
    else
    {
        readyWeapon(fighter, t, true);
    }
    PED::REGISTER_TARGET(fighter.ped, target, true);
    AI::TASK_GO_TO_COORD_WHILE_AIMING_AT_ENTITY(
        fighter.ped,
        moveTo.x,
        moveTo.y,
        moveTo.z,
        target,
        std::min(4.0f, combatMoveSpeedForFighter(fighter) * (eliteDuel ? 1.12f : 1.0f)),
        true,
        1.5f,
        4.0f,
        true,
        0,
        true,
        joaat("FIRING_PATTERN_FULL_AUTO"),
        0,
        0);
    fighter.lastRepositionTask = t;
    fighter.lastTask = t;
    scheduleScriptedCombatResume(fighter, t, 1700u);
    return true;
}

DWORD bossEvasiveCooldown(const Fighter& fighter)
{
    return kBosses[static_cast<size_t>(fighter.boss)].evasiveCooldownMs;
}

int bossSlideDiveChance(const Fighter& fighter, float dist)
{
    bool close = dist < 28.0f * 28.0f;
    const BossDef& boss = kBosses[static_cast<size_t>(fighter.boss)];
    return close ? boss.slideDiveChanceClose : boss.slideDiveChanceFar;
}

int bossDodgeDeadEyeBlockChance(const Fighter& fighter)
{
    if (fighter.boss == kBossJohn || fighter.boss == kBossMicah || fighter.boss == kBossArthur)
        return 100;
    return kBosses[static_cast<size_t>(fighter.boss)].dodgeDeadEyeBlockChance;
}

int bossMinimumBurstsBeforeMovement(const Fighter& fighter)
{
    switch (fighter.boss)
    {
    case kBossMicah:
        return 3;
    case kBossDutch:
        return 3;
    case kBossJohn:
    case kBossArthur:
        return 1;
    default:
        return 2;
    }
}

bool validateEvasionDestination(Vec3 self, Vec3& destination)
{
    float originalZ = destination.z;
    snapToGround(destination);
    if (std::fabs(destination.z - self.z) > 4.0f)
        return false;

    float waterHeight{};
    if (WATER::GET_WATER_HEIGHT(destination.x, destination.y, originalZ + 2.0f, &waterHeight) &&
        waterHeight > destination.z - 0.25f)
    {
        return false;
    }

    return true;
}

bool bossUnderSustainedFire(const Fighter& fighter, DWORD t)
{
    return fighter.recentDamageHits >= 2 &&
        fighter.recentDamageWindowStarted != 0 &&
        t - fighter.recentDamageWindowStarted <= 4500u;
}

void markBossBurst(Fighter& fighter, DWORD t)
{
    fighter.lastShotTask = t;
    if (fighter.difficulty == Difficulty::Bosses)
        fighter.bossBurstsSinceMovement = std::min(8, fighter.bossBurstsSinceMovement + 1);
}

bool isMobileFireBoss(const Fighter& fighter)
{
    return fighter.difficulty == Difficulty::Bosses &&
        (fighter.boss == kBossJohn || fighter.boss == kBossArthur);
}

bool pedDoingCombatRoll(Ped ped)
{
    return exists(ped) && PED::_0xC48A9EB0D499B3E5(ped) != 0;
}

bool tryStartNativeCombatDive(Fighter& fighter, Ped target, DWORD t, int direction)
{
    (void)fighter;
    (void)target;
    (void)t;
    (void)direction;
#if 0
    // TASK_EVASIVE_ANIM is exposed by the local SDK as AI::_0x5F22926E1BCE9B08.
    // Keep this disabled until the argument layout is verified against reliable
    // native documentation or repeated in-game testing.
    AI::_0x5F22926E1BCE9B08(fighter.ped, target, direction);
    return pedDoingCombatRoll(fighter.ped);
#endif
    return false;
}

DWORD playerThreatDodgeCooldown(const Fighter& fighter)
{
    return fighter.boss == kBossArthur ? kArthurPlayerDodgeCooldownMs : kJohnPlayerDodgeCooldownMs;
}

bool playerIsActivelyThreateningBoss(
    Fighter& fighter,
    DWORD t,
    bool& directlyAiming,
    bool& recentlyDamagedByPlayer)
{
    directlyAiming = false;
    recentlyDamagedByPlayer = false;

    if (!isMobileFireBoss(fighter) ||
        !g_runtime.playerParticipating ||
        g_runtime.playerSpectating ||
        g_runtime.playerEliminated)
    {
        fighter.playerAimPressureActive = false;
        fighter.playerAimPressureStartedAt = 0;
        return false;
    }

    Ped player = playerPed();
    Player playerId = PLAYER::PLAYER_ID();
    if (!exists(player) ||
        PLAYER::IS_PLAYER_DEAD(playerId) ||
        PED::IS_PED_DEAD_OR_DYING(player, true) ||
        PED::IS_PED_FATALLY_INJURED(player) ||
        !exists(fighter.ped))
    {
        fighter.playerAimPressureActive = false;
        fighter.playerAimPressureStartedAt = 0;
        return false;
    }

    bool freeAiming = PLAYER::IS_PLAYER_FREE_AIMING_AT_ENTITY(playerId, fighter.ped) != 0;
    bool targeting = PLAYER::IS_PLAYER_TARGETTING_ENTITY(playerId, fighter.ped, true) != 0;
    bool firingAtBoss = (freeAiming || targeting) && PED::IS_PED_SHOOTING(player) != 0;
    directlyAiming = freeAiming || targeting || firingAtBoss;

    if (directlyAiming)
    {
        if (!fighter.playerAimPressureActive)
            fighter.playerAimPressureStartedAt = t;
        fighter.playerAimPressureActive = true;
    }
    else
    {
        fighter.playerAimPressureActive = false;
        fighter.playerAimPressureStartedAt = 0;
    }

    if (ENTITY::HAS_ENTITY_BEEN_DAMAGED_BY_ENTITY(fighter.ped, player, true, true))
        fighter.lastPlayerDamage = t;
    recentlyDamagedByPlayer = fighter.lastPlayerDamage != 0 && t - fighter.lastPlayerDamage < 1600u;

    return directlyAiming || recentlyDamagedByPlayer;
}

bool canPlayerThreatBossDodgeUsePlayerAsTarget(const Fighter& fighter)
{
    Ped player = playerPed();
    return isValidEnemyTarget(fighter, player);
}

bool finite2(float x, float y)
{
    return std::isfinite(x) && std::isfinite(y);
}

struct BossDashCandidate
{
    Vec3 position{};
    float sideX = 0.0f;
    float sideY = 0.0f;
    float backX = 0.0f;
    float backY = 0.0f;
    float sideSign = 0.0f;
    float sideDistance = 0.0f;
    float backDistance = 0.0f;
    float score = 0.0f;
    bool valid = false;
};

bool evaluateBossDashCandidate(
    Vec3 self,
    Vec3 threatPos,
    float sideSign,
    float sideDistance,
    float backDistance,
    BossDashCandidate& candidate)
{
    float dx = threatPos.x - self.x;
    float dy = threatPos.y - self.y;
    float len = std::sqrt(std::max(0.001f, dx * dx + dy * dy));
    float sideX = (-dy / len) * sideSign;
    float sideY = (dx / len) * sideSign;
    float backX = -(dx / len);
    float backY = -(dy / len);
    if (!finite2(sideX, sideY) || !finite2(backX, backY))
        return false;

    Vec3 pos{
        self.x + sideX * sideDistance + backX * backDistance,
        self.y + sideY * sideDistance + backY * backDistance,
        self.z
    };
    float rawZ = pos.z;
    snapToGround(pos);
    float heightDelta = std::fabs(pos.z - self.z);
    if (heightDelta > 4.0f)
        return false;

    float waterHeight{};
    if (WATER::GET_WATER_HEIGHT(pos.x, pos.y, rawZ + 2.0f, &waterHeight) &&
        waterHeight > pos.z - 0.25f)
    {
        return false;
    }

    float separation = std::sqrt(distanceSquared(pos, threatPos));
    candidate.position = pos;
    candidate.sideX = sideX;
    candidate.sideY = sideY;
    candidate.backX = backX;
    candidate.backY = backY;
    candidate.sideSign = sideSign;
    candidate.sideDistance = sideDistance;
    candidate.backDistance = backDistance;
    candidate.score = separation + sideDistance * 0.35f - heightDelta * 5.0f + randomFloat(0.0f, 0.35f);
    candidate.valid = true;
    return true;
}

bool chooseBossDashDestination(
    Vec3 self,
    Vec3 threatPos,
    bool playerTriggered,
    float preferredSign,
    bool shorterFallback,
    BossDashCandidate& best)
{
    best = {};
    std::array<float, 2> signs{ -1.0f, 1.0f };
    if (preferredSign != 0.0f)
        signs = { { preferredSign, -preferredSign } };

    float sideMin = playerTriggered ? 13.0f : 10.5f;
    float sideMax = playerTriggered ? 16.0f : 10.5f;
    float backMin = playerTriggered ? 1.0f : 2.4f;
    float backMax = playerTriggered ? 2.5f : 2.4f;
    if (shorterFallback)
    {
        sideMin = 8.0f;
        sideMax = 11.0f;
        backMin = 0.8f;
        backMax = 1.8f;
    }

    for (float sign : signs)
    {
        for (int attempt = 0; attempt < 2; ++attempt)
        {
            float sideDistance = randomFloat(sideMin, sideMax);
            float backDistance = randomFloat(backMin, backMax);
            BossDashCandidate candidate{};
            if (!evaluateBossDashCandidate(self, threatPos, sign, sideDistance, backDistance, candidate))
                continue;

            if (!best.valid || candidate.score > best.score)
                best = candidate;
        }
    }

    return best.valid;
}

bool issueBossMoveAndShootDash(
    Fighter& fighter,
    Ped evasionThreat,
    Ped aimTarget,
    Ped firingTarget,
    bool shootDuringDash,
    const BossDashCandidate& destination,
    DWORD t,
    bool playerTriggered,
    bool highIntensityNpcDuel = false)
{
    if (!exists(fighter.ped) || !exists(evasionThreat) || !exists(aimTarget))
        return false;

    Hash current = currentNormalWeapon(fighter);
    if (current)
    {
        fighter.combatWeapon = current;
        fillWeaponAmmo(fighter.ped, current);
    }
    else
    {
        readyWeapon(fighter, t, true);
    }

    float speed = playerTriggered ? randomFloat(9.0f, 11.0f) : (highIntensityNpcDuel ? randomFloat(7.9f, 9.4f) : 6.35f);
    DWORD duration = playerTriggered ? kPlayerDashDurationMs : (highIntensityNpcDuel ? 720u : kMobileBossDashMs);

    AI::CLEAR_PED_TASKS(fighter.ped, true, false);
    setPedCrouchMovement(fighter.ped, false);
    fighter.crouchUntil = 0;
    PED::SET_PED_SHOOT_RATE(fighter.ped, bossShootRate(fighter));
    if (exists(firingTarget))
        PED::REGISTER_TARGET(fighter.ped, firingTarget, true);

    AI::TASK_GO_TO_COORD_WHILE_AIMING_AT_ENTITY(
        fighter.ped,
        destination.position.x,
        destination.position.y,
        destination.position.z,
        aimTarget,
        speed,
        shootDuringDash,
        0.25f,
        1.15f,
        true,
        0,
        true,
        joaat("FIRING_PATTERN_FULL_AUTO"),
        0,
        0);

    if (exists(firingTarget) && fighter.currentTarget != firingTarget)
        fighter.currentTargetStartedAt = t;
    if (exists(firingTarget))
        fighter.currentTarget = firingTarget;

    fighter.scriptedActionType = ScriptedActionType::BossEvasion;
    fighter.scriptedActionStartedAt = t;
    fighter.scriptedActionResumeAt = t + duration;
    fighter.scriptedActionTimeoutAt = fighter.scriptedActionResumeAt + 650u;
    fighter.evasionStartPos = entityCoords(fighter.ped);
    fighter.evasionTargetPos = destination.position;
    fighter.evasionStyle = BossEvasionStyle::MoveAndShootDash;
    fighter.evasionTaskRequested = true;
    fighter.evasionActuallyStarted = false;
    fighter.evasionFinished = false;
    fighter.evasionPlayerTriggered = playerTriggered;
    fighter.evasionShootDuringDash = shootDuringDash;
    fighter.evasionVelocityFallbackApplied = false;
    fighter.evasionThreat = evasionThreat;
    fighter.evasionAimTarget = aimTarget;
    fighter.evasionFiringTarget = firingTarget;
    fighter.evasionSideX = destination.sideX;
    fighter.evasionSideY = destination.sideY;
    fighter.evasionBackX = destination.backX;
    fighter.evasionBackY = destination.backY;
    fighter.evasionTaskSpeed = speed;
    fighter.evasionDashDurationMs = duration;
    fighter.evasionRequestedAt = t;
    fighter.evasionStartedAt = 0;
    fighter.evasionExpectedEndAt = fighter.scriptedActionResumeAt;
    fighter.evasionDeadEyeBlockStartedAt = 0;
    fighter.evasionDeadEyeBlockUntil = 0;
    fighter.evasionFollowUpAt = fighter.scriptedActionResumeAt;
    fighter.evasionDeadEyeSuppressed = false;
    fighter.evasionShotsObserved = false;
    fighter.evasionSideSign = destination.sideSign;
    fighter.bossBurstsSinceMovement = 0;
    fighter.lastEvasiveTask = t;
    fighter.lastRepositionTask = t;
    fighter.lastTask = t;
    return true;
}

bool retryBossEvasionOppositeSide(Fighter& fighter, DWORD t)
{
    if (!fighter.evasionPlayerTriggered ||
        fighter.evasionFallbackAttempts >= 1 ||
        !exists(fighter.evasionThreat) ||
        !exists(fighter.evasionAimTarget))
    {
        return false;
    }

    BossDashCandidate destination{};
    Vec3 self = entityCoords(fighter.ped);
    Vec3 threatPos = entityCoords(fighter.evasionThreat);
    float oppositeSign = fighter.evasionSideSign == 0.0f ? 0.0f : -fighter.evasionSideSign;
    if (!chooseBossDashDestination(self, threatPos, true, oppositeSign, true, destination))
        return false;

    ++fighter.evasionFallbackAttempts;
    bool issued = issueBossMoveAndShootDash(
        fighter,
        fighter.evasionThreat,
        fighter.evasionAimTarget,
        fighter.evasionFiringTarget,
        fighter.evasionShootDuringDash,
        destination,
        t,
        true);
    if (issued)
    {
        fighter.evasionFallbackAttempts = 1;
        debugActionState(fighter, "boss-player-evasion-opposite-side-retry");
    }
    return issued;
}

bool applyBossEvasionVelocityFallback(Fighter& fighter, DWORD t)
{
    if (!fighter.evasionPlayerTriggered ||
        fighter.evasionVelocityFallbackApplied ||
        !finite2(fighter.evasionSideX, fighter.evasionSideY))
    {
        return false;
    }

    float speed = randomFloat(7.0f, 8.4f);
    ENTITY::SET_ENTITY_VELOCITY(
        fighter.ped,
        fighter.evasionSideX * speed,
        fighter.evasionSideY * speed,
        0.05f);
    fighter.evasionVelocityFallbackApplied = true;
    fighter.evasionRequestedAt = t;
    fighter.evasionStartPos = entityCoords(fighter.ped);
    debugActionState(fighter, "boss-player-evasion-velocity-fallback");
    return true;
}

bool updateBossEvasionStart(Fighter& fighter, DWORD t)
{
    if (fighter.evasionActuallyStarted || !fighter.evasionTaskRequested)
        return true;

    if (!exists(fighter.ped))
        return false;

    DWORD elapsed = t - fighter.evasionRequestedAt;
    if (elapsed < kPlayerDashConfirmMs)
        return true;

    Vec3 pos = entityCoords(fighter.ped);
    float moved = distanceSquared(pos, fighter.evasionStartPos);
    bool running =
        AI::IS_PED_RUNNING(fighter.ped) ||
        AI::IS_PED_SPRINTING(fighter.ped);
    if (moved >= 0.55f * 0.55f || running)
    {
        fighter.evasionActuallyStarted = true;
        fighter.evasionStartedAt = t;
        if (fighter.evasionPlayerTriggered)
            startBossDodgeDeadEyeBlock(fighter, fighter.evasionThreat, t);
        debugActionState(fighter, fighter.evasionPlayerTriggered ? "boss-player-evasion-confirmed" : "boss-evasion-confirmed");
        return true;
    }

    if (!fighter.evasionPlayerTriggered)
    {
        if (elapsed >= kPlayerDashFallbackMs)
        {
            fighter.evasionActuallyStarted = true;
            fighter.evasionStartedAt = t;
        }
        return true;
    }

    if (elapsed < kPlayerDashFallbackMs)
        return true;

    if (retryBossEvasionOppositeSide(fighter, t))
        return true;

    if (applyBossEvasionVelocityFallback(fighter, t))
        return true;

    debugActionState(fighter, "boss-player-evasion-failed-to-start");
    return false;
}

void recoverFromBossEvasion(Fighter& fighter, DWORD t)
{
    Ped target = isValidEnemyTarget(fighter, fighter.evasionFiringTarget) ?
        fighter.evasionFiringTarget :
        (isValidEnemyTarget(fighter, fighter.currentTarget) ? fighter.currentTarget : 0);

    resetScriptedActionState(fighter, false);
    fighter.lastShotTask = 0;

    if (!exists(target))
        return;

    Hash current = currentNormalWeapon(fighter);
    if (current)
    {
        fighter.combatWeapon = current;
        fillWeaponAmmo(fighter.ped, current);
    }
    PED::SET_PED_COMBAT_MOVEMENT(fighter.ped, bossNativeCombatMovement(fighter));
    taskBossAttackBurst(fighter, target, t, false, false);
    debugActionState(fighter, "boss-evasion-recovery-burst");
}

void taskBossAttackBurst(Fighter& fighter, Ped target, DWORD t, bool inCover, bool woundedBoss)
{
    int duration = bossShotDuration(fighter, woundedBoss);
    readyWeapon(fighter, t, true);
    PED::REGISTER_TARGET(fighter.ped, target, true);
    PED::SET_PED_SHOOT_RATE(fighter.ped, bossShootRate(fighter));
    PED::SET_PED_FIRING_PATTERN(fighter.ped, joaat("FIRING_PATTERN_FULL_AUTO"));
    PED::SET_PED_COMBAT_MOVEMENT(fighter.ped, inCover ? 1 : bossNativeCombatMovement(fighter));

    if (inCover)
    {
        AI::TASK_SHOOT_AT_ENTITY(
            fighter.ped,
            target,
            std::max(750, duration),
            joaat("FIRING_PATTERN_FULL_AUTO"),
            true);
        markBossBurst(fighter, t);
        fighter.lastTask = t;
        scheduleScriptedCombatResume(fighter, t, 650u);
        return;
    }

    AI::TASK_COMBAT_PED(fighter.ped, target, 0, 16);
    markBossBurst(fighter, t);
    fighter.lastTask = t;
    scheduleScriptedCombatResume(fighter, t, inCover ? 700u : static_cast<DWORD>(std::min(duration, 950)));
}

DWORD bossNativeCoverDelay(const Fighter& fighter, bool woundedBoss)
{
    const BossDef& boss = kBosses[static_cast<size_t>(fighter.boss)];
    DWORD base = woundedBoss ? boss.woundedCoverDelayMs : boss.coverDelayMs;
    switch (fighter.boss)
    {
    case kBossDutch:
        return std::max<DWORD>(900u, (base * 60u) / 100u);
    case kBossJohn:
    case kBossArthur:
        return std::max<DWORD>(950u, (base * 65u) / 100u);
    case kBossColm:
        return std::max<DWORD>(1000u, (base * 70u) / 100u);
    case kBossMicah:
        return std::max<DWORD>(1250u, (base * 80u) / 100u);
    default:
        return std::max<DWORD>(1100u, base);
    }
}

int bossNativeCoverChance(const Fighter& fighter, bool woundedBoss, bool sustainedFire)
{
    if (woundedBoss)
        return 92;
    if (sustainedFire)
    {
        switch (fighter.boss)
        {
        case kBossDutch:
            return 86;
        case kBossJohn:
        case kBossArthur:
            return 72;
        case kBossColm:
            return 80;
        case kBossMicah:
            return 46;
        default:
            return 64;
        }
    }

    switch (fighter.boss)
    {
    case kBossDutch:
        return 34;
    case kBossColm:
        return 28;
    case kBossJohn:
    case kBossArthur:
        return 20;
    case kBossMicah:
        return 10;
    default:
        return 18;
    }
}

bool tryBossNativeCover(Fighter& fighter, Ped target, DWORD t, float dist, bool canSeeTarget, bool woundedBoss)
{
    if (fighter.difficulty != Difficulty::Bosses ||
        g_menu.battleType != BattleType::AllWeapons ||
        !exists(target) ||
        protectedScriptedActionActive(fighter) ||
        weaponControllerSettling(fighter, t) ||
        PED::IS_PED_IN_COVER(fighter.ped, false, false) ||
        PED::IS_PED_AIMING_FROM_COVER(fighter.ped) ||
        PED::IS_PED_GOING_INTO_COVER(fighter.ped))
    {
        return false;
    }

    DWORD coverDelay = bossNativeCoverDelay(fighter, woundedBoss);
    if (t - fighter.lastDefensiveTask < coverDelay)
        return false;

    bool sustainedFire = bossUnderSustainedFire(fighter, t);
    bool targetShooting = exists(target) && PED::IS_PED_SHOOTING(target) != 0;
    bool farEnoughForCover = dist > 12.0f * 12.0f && dist < 100.0f * 100.0f;
    if (!farEnoughForCover || (!canSeeTarget && !sustainedFire))
        return false;

    int chance = bossNativeCoverChance(fighter, woundedBoss, sustainedFire);
    if (targetShooting)
        chance = std::min(96, chance + 14);
    if (randomRange(1, 100) > chance)
        return false;

    readyWeapon(fighter, t, true);
    PED::REGISTER_TARGET(fighter.ped, target, true);
    PED::SET_PED_SHOOT_RATE(fighter.ped, bossShootRate(fighter));
    PED::SET_PED_FIRING_PATTERN(fighter.ped, joaat("FIRING_PATTERN_FULL_AUTO"));
    PED::SET_PED_COMBAT_MOVEMENT(fighter.ped, 1);
    AI::TASK_SEEK_COVER_FROM_PED(fighter.ped, target, woundedBoss ? 4200 : 3200, false, false, false);
    AI::TASK_COMBAT_PED(fighter.ped, target, 0, 16);

    if (fighter.currentTarget != target)
        fighter.currentTargetStartedAt = t;
    fighter.currentTarget = target;
    fighter.defensiveCombatStartedAt = t;
    fighter.defensiveCombatUntil = t + (woundedBoss ? 9000u : 6200u);
    fighter.lastDefensiveTask = t;
    fighter.lastTask = t;
    scheduleScriptedCombatResume(fighter, t, woundedBoss ? 1550u : 1150u);
    return true;
}

DWORD bossNativeRepositionDelay(const Fighter& fighter)
{
    switch (fighter.boss)
    {
    case kBossJohn:
    case kBossArthur:
        return 720u;
    case kBossMicah:
        return 820u;
    case kBossColm:
        return 1150u;
    case kBossDutch:
        return 1350u;
    default:
        return 1050u;
    }
}

int bossNativeRepositionChance(const Fighter& fighter, bool sustainedFire, bool playerThreat, bool eliteDuel)
{
    if (sustainedFire)
    {
        switch (fighter.boss)
        {
        case kBossJohn:
        case kBossArthur:
            return 100;
        case kBossMicah:
            return 96;
        case kBossColm:
            return 90;
        case kBossDutch:
            return 78;
        default:
            return 90;
        }
    }

    if (playerThreat)
    {
        switch (fighter.boss)
        {
        case kBossJohn:
        case kBossArthur:
            return 100;
        case kBossMicah:
            return 94;
        case kBossColm:
            return 82;
        case kBossDutch:
            return 68;
        default:
            return 82;
        }
    }

    int chance = eliteDuel ? 58 : 38;
    switch (fighter.boss)
    {
    case kBossJohn:
    case kBossArthur:
        chance += eliteDuel ? 34 : 30;
        break;
    case kBossMicah:
        chance += eliteDuel ? 27 : 23;
        break;
    case kBossColm:
        chance += eliteDuel ? 16 : 12;
        break;
    case kBossDutch:
        chance += eliteDuel ? 4 : 2;
        break;
    default:
        break;
    }
    return std::clamp(chance, 12, 96);
}

float bossNativeRepositionSpeed(const Fighter& fighter, bool playerThreat)
{
    float speed = combatMoveSpeedForFighter(fighter);
    switch (fighter.boss)
    {
    case kBossJohn:
    case kBossArthur:
        speed += playerThreat ? 1.90f : 1.35f;
        break;
    case kBossMicah:
        speed += playerThreat ? 1.55f : 1.15f;
        break;
    case kBossDutch:
        speed += 1.00f;
        break;
    case kBossColm:
        speed += 1.15f;
        break;
    default:
        break;
    }
    return std::clamp(speed, 2.75f, 5.0f);
}

bool tryBossNativeRepositionRun(Fighter& fighter, Ped target, DWORD t, float dist, bool canSeeTarget)
{
    if (fighter.difficulty != Difficulty::Bosses ||
        g_menu.battleType != BattleType::AllWeapons ||
        !exists(target) ||
        protectedScriptedActionActive(fighter) ||
        weaponControllerSettling(fighter, t) ||
        PED::IS_PED_GOING_INTO_COVER(fighter.ped))
    {
        return false;
    }

    bool currentlyInCover =
        PED::IS_PED_IN_COVER(fighter.ped, false, false) ||
        PED::IS_PED_AIMING_FROM_COVER(fighter.ped);
    DWORD delay = bossNativeRepositionDelay(fighter);
    if (t - fighter.lastRepositionTask < delay || t - fighter.lastEvasiveTask < delay)
        return false;

    float preferredRange = preferredGunRangeForFighter(fighter);
    float minDistance = fighter.boss == kBossMicah ? 7.0f : 10.0f;
    float maxDistance = std::max(72.0f, preferredRange + 26.0f);
    if (dist < minDistance * minDistance || dist > maxDistance * maxDistance)
        return false;

    bool sustainedFire = bossUnderSustainedFire(fighter, t);
    bool playerThreat = playerCanBeBossDodgeDeadEyeBlocked(fighter, target, t);
    bool eliteDuel = eliteNpcDuelTarget(fighter, target);
    bool coverStale =
        currentlyInCover &&
        fighter.defensiveCombatStartedAt != 0 &&
        t - fighter.defensiveCombatStartedAt > 2600u;
    if (currentlyInCover && !sustainedFire && !playerThreat && !coverStale)
        return false;
    if (!sustainedFire && !playerThreat && !canSeeTarget && dist < (preferredRange + 8.0f) * (preferredRange + 8.0f))
        return false;

    int chance = bossNativeRepositionChance(fighter, sustainedFire, playerThreat, eliteDuel);
    if (fighter.bossBurstsSinceMovement >= bossMinimumBurstsBeforeMovement(fighter))
        chance = std::min(100, chance + 30);
    if (randomRange(1, 100) > chance)
        return false;

    Vec3 self = entityCoords(fighter.ped);
    Vec3 targetPos = entityCoords(target);
    float dx = targetPos.x - self.x;
    float dy = targetPos.y - self.y;
    float len = std::sqrt(std::max(0.001f, dx * dx + dy * dy));
    float sideSign = randomRange(0, 1) == 0 ? -1.0f : 1.0f;
    float sideX = (-dy / len) * sideSign;
    float sideY = (dx / len) * sideSign;
    float forwardX = dx / len;
    float forwardY = dy / len;

    float sideDistance = randomFloat(8.0f, 13.0f);
    float forwardDistance = dist > preferredRange * preferredRange ? randomFloat(4.0f, 10.0f) : randomFloat(-7.0f, 2.5f);
    if (fighter.boss == kBossJohn || fighter.boss == kBossArthur)
    {
        sideDistance = randomFloat(15.0f, 24.0f);
        forwardDistance = dist > preferredRange * preferredRange ? randomFloat(7.0f, 15.0f) : randomFloat(-9.0f, 4.0f);
    }
    else if (fighter.boss == kBossMicah)
    {
        sideDistance = randomFloat(13.0f, 20.0f);
        forwardDistance = dist > preferredRange * preferredRange ? randomFloat(8.0f, 16.0f) : randomFloat(1.0f, 7.0f);
    }
    else if (fighter.boss == kBossDutch)
    {
        sideDistance = randomFloat(8.0f, 13.0f);
        forwardDistance = dist > preferredRange * preferredRange ? randomFloat(2.0f, 7.0f) : randomFloat(-6.0f, 2.0f);
    }

    Vec3 moveTo{
        self.x + sideX * sideDistance + forwardX * forwardDistance,
        self.y + sideY * sideDistance + forwardY * forwardDistance,
        self.z
    };
    if (!validateEvasionDestination(self, moveTo))
    {
        moveTo = {
            self.x - sideX * sideDistance + forwardX * forwardDistance,
            self.y - sideY * sideDistance + forwardY * forwardDistance,
            self.z
        };
        if (!validateEvasionDestination(self, moveTo))
            return false;
    }

    readyWeapon(fighter, t, true);
    PED::REGISTER_TARGET(fighter.ped, target, true);
    PED::SET_PED_SHOOT_RATE(fighter.ped, bossShootRate(fighter));
    PED::SET_PED_FIRING_PATTERN(fighter.ped, joaat("FIRING_PATTERN_FULL_AUTO"));
    PED::SET_PED_COMBAT_MOVEMENT(fighter.ped, bossNativeCombatMovement(fighter));
    float runSpeed = bossNativeRepositionSpeed(fighter, playerThreat);
    AI::SET_PED_DESIRED_MOVE_BLEND_RATIO(fighter.ped, runSpeed);
    PED::SET_PED_MOVE_RATE_OVERRIDE(fighter.ped, std::min(5.0f, runSpeed * 1.05f));
    PED::SET_PED_MAX_MOVE_BLEND_RATIO(fighter.ped, std::min(5.0f, runSpeed * 1.05f));
    setPedCrouchMovement(fighter.ped, false);
    fighter.crouchUntil = 0;
    if (currentlyInCover)
        AI::CLEAR_PED_TASKS(fighter.ped, true, false);

    AI::TASK_GO_TO_COORD_WHILE_AIMING_AT_ENTITY(
        fighter.ped,
        moveTo.x,
        moveTo.y,
        moveTo.z,
        target,
        runSpeed,
        true,
        0.45f,
        2.25f,
        true,
        0,
        true,
        joaat("FIRING_PATTERN_FULL_AUTO"),
        0,
        0);

    if (fighter.currentTarget != target)
        fighter.currentTargetStartedAt = t;
    fighter.currentTarget = target;
    if (currentlyInCover)
    {
        fighter.defensiveCombatStartedAt = 0;
        fighter.defensiveCombatUntil = 0;
    }
    fighter.bossBurstsSinceMovement = 0;
    fighter.lastEvasiveTask = t;
    fighter.lastRepositionTask = t;
    fighter.lastTask = t;
    fighter.lastObservedMovementAt = t;
    fighter.lastCombatActivityAt = t;
    if (playerThreat)
        startBossMovementDeadEyeBlock(fighter, target, t);
    scheduleScriptedCombatResume(fighter, t, std::max<DWORD>(bossDodgeDeadEyeDuration(), 900u));
    debugActionState(fighter, "boss-native-reposition-run");
    return true;
}

bool bossShouldEvade(Fighter& fighter, Ped target, DWORD t, bool canSeeTarget)
{
    if (fighter.difficulty != Difficulty::Bosses)
        return false;

    Ped player = playerPed();
    Player playerId = PLAYER::PLAYER_ID();
    bool mobileBoss = isMobileFireBoss(fighter);
    bool playerPressure =
        !mobileBoss &&
        exists(player) &&
        g_runtime.playerParticipating &&
        !g_runtime.playerSpectating &&
        !g_runtime.playerEliminated &&
        !PLAYER::IS_PLAYER_DEAD(playerId) &&
        (PLAYER::IS_PLAYER_FREE_AIMING_AT_ENTITY(playerId, fighter.ped) ||
         PLAYER::IS_PLAYER_TARGETTING_ENTITY(playerId, fighter.ped, true));
    bool recentlyHit = bossUnderSustainedFire(fighter, t);
    bool eliteDuel = eliteNpcDuelTarget(fighter, target);
    int playerChance = 65;
    int hitChance = 82;
    int combatChance = 2;
    switch (fighter.boss)
    {
    case kBossJohn:
    case kBossArthur:
        playerChance = 100;
        hitChance = 100;
        combatChance = 10;
        break;
    case kBossMicah:
        playerChance = 45;
        hitChance = 78;
        combatChance = 1;
        break;
    case kBossDutch:
        playerChance = 15;
        hitChance = 72;
        combatChance = 0;
        break;
    case kBossColm:
        playerChance = 25;
        hitChance = 74;
        combatChance = 1;
        break;
    default:
        break;
    }
    if (eliteDuel)
    {
        hitChance = std::max(hitChance, isMobileFireBoss(fighter) ? 94 : 84);
        combatChance += isMobileFireBoss(fighter) ? 18 : 10;
    }

    bool pressuredByPlayer = playerPressure && randomRange(0, 100) < playerChance;
    bool pressuredByHit = recentlyHit && randomRange(0, 100) < hitChance;
    bool combatPressure = canSeeTarget && randomRange(0, 100) < combatChance;
    int visibleGunfightChance = eliteDuel ? (mobileBoss ? 44 : 28) : (mobileBoss ? 24 : 0);
    bool visibleGunfight =
        canSeeTarget &&
        target != player &&
        PED::IS_PED_SHOOTING(target) != 0 &&
        randomRange(0, 100) < visibleGunfightChance;
    bool burstCyclePressure =
        canSeeTarget &&
        fighter.bossBurstsSinceMovement >= bossMinimumBurstsBeforeMovement(fighter) &&
        randomRange(0, 100) < (eliteDuel ? (mobileBoss ? 32 : 18) : (mobileBoss ? 14 : 0));
    return pressuredByPlayer || pressuredByHit || combatPressure || visibleGunfight || burstCyclePressure;
}

bool tryBossEvasiveBurst(Fighter& fighter, Ped target, DWORD t, float dist, bool canSeeTarget)
{
    bool sustainedFire = bossUnderSustainedFire(fighter, t);
    bool eliteDuel = eliteNpcDuelTarget(fighter, target);
    DWORD evasiveCooldown = eliteDuel ?
        std::max<DWORD>(900u, (bossEvasiveCooldown(fighter) * 55u) / 100u) :
        bossEvasiveCooldown(fighter);
    float maxEvasiveDistance = eliteDuel ? 84.0f : 70.0f;
    int requiredBurstsBeforeMovement = bossMinimumBurstsBeforeMovement(fighter);
    if (eliteDuel)
        requiredBurstsBeforeMovement = std::max(1, requiredBurstsBeforeMovement - 1);
    bool startedInCover =
        PED::IS_PED_IN_COVER(fighter.ped, false, false) ||
        PED::IS_PED_AIMING_FROM_COVER(fighter.ped);
    if (fighter.difficulty != Difficulty::Bosses ||
        g_menu.battleType != BattleType::AllWeapons ||
        !exists(target) ||
        protectedScriptedActionActive(fighter) ||
        weaponControllerSettling(fighter, t) ||
        (!sustainedFire && !isMobileFireBoss(fighter) && fighter.bossBurstsSinceMovement < requiredBurstsBeforeMovement) ||
        t - fighter.lastEvasiveTask < evasiveCooldown ||
        t - fighter.lastEvasionEligibilityCheck < kBossEvasionCheckMs ||
        dist < 6.0f * 6.0f ||
        dist > maxEvasiveDistance * maxEvasiveDistance)
    {
        return false;
    }
    fighter.lastEvasionEligibilityCheck = t;
    if (!bossShouldEvade(fighter, target, t, canSeeTarget))
        return false;

    Vec3 self = entityCoords(fighter.ped);
    Vec3 targetPos = entityCoords(target);
    float dx = targetPos.x - self.x;
    float dy = targetPos.y - self.y;
    float len = std::sqrt(std::max(0.001f, dx * dx + dy * dy));
    float sideSign = randomRange(0, 1) == 0 ? -1.0f : 1.0f;
    float sideX = (-dy / len) * sideSign;
    float sideY = (dx / len) * sideSign;
    float backX = -(dx / len);
    float backY = -(dy / len);
    bool slideDive = isMobileFireBoss(fighter) || randomRange(0, 100) < bossSlideDiveChance(fighter, dist);
    if (!slideDive)
        return false;

    bool mobileDodge = isMobileFireBoss(fighter);
    float sideDistance = mobileDodge ? 10.5f : 18.0f;
    float backDistance = fighter.boss == kBossMicah ? 1.6f : 4.2f;
    if (mobileDodge)
        backDistance = 2.4f;
    if (fighter.boss == kBossDutch)
    {
        sideDistance = 11.0f;
        backDistance = 2.0f;
    }
    Vec3 evadeTo{
        self.x + sideX * sideDistance + backX * backDistance,
        self.y + sideY * sideDistance + backY * backDistance,
        self.z
    };
    if (!validateEvasionDestination(self, evadeTo))
    {
        sideX = -sideX;
        sideY = -sideY;
        evadeTo = {
            self.x + sideX * (sideDistance * 0.72f) + backX * backDistance,
            self.y + sideY * (sideDistance * 0.72f) + backY * backDistance,
            self.z
        };
        if (!validateEvasionDestination(self, evadeTo))
            return false;
    }

    AI::CLEAR_PED_TASKS(fighter.ped, true, false);
    readyWeapon(fighter, t, true);
    PED::REGISTER_TARGET(fighter.ped, target, true);
    if (fighter.currentTarget != target)
        fighter.currentTargetStartedAt = t;
    fighter.currentTarget = target;
    setPedCrouchMovement(fighter.ped, !mobileDodge);
    fighter.crouchUntil = mobileDodge ? 0 : t + 1450u;
    PED::SET_PED_SHOOT_RATE(fighter.ped, bossShootRate(fighter));
    fighter.bossBurstsSinceMovement = 0;
    if (sustainedFire)
    {
        if (isMobileFireBoss(fighter))
        {
            fighter.defensiveCombatStartedAt = 0;
            fighter.defensiveCombatUntil = 0;
            PED::SET_PED_COMBAT_MOVEMENT(fighter.ped, bossNativeCombatMovement(fighter));
        }
        else if (startedInCover)
        {
            fighter.defensiveCombatStartedAt = 0;
            fighter.defensiveCombatUntil = 0;
            PED::SET_PED_COMBAT_MOVEMENT(fighter.ped, bossNativeCombatMovement(fighter));
        }
        else
        {
            if (fighter.defensiveCombatStartedAt == 0)
                fighter.defensiveCombatStartedAt = t;
            fighter.defensiveCombatUntil = t + 9000u;
            PED::SET_PED_COMBAT_MOVEMENT(fighter.ped, 1);
        }
        fighter.recentDamageHits = 0;
        fighter.recentDamageWindowStarted = 0;
    }

    if (mobileDodge && eliteDuel)
    {
        BossDashCandidate destination{};
        if ((chooseBossDashDestination(self, targetPos, true, sideSign, false, destination) ||
             chooseBossDashDestination(self, targetPos, true, sideSign, true, destination)) &&
            issueBossMoveAndShootDash(fighter, target, target, target, true, destination, t, false, true))
        {
            ENTITY::CLEAR_ENTITY_LAST_DAMAGE_ENTITY(fighter.ped);
            PED::CLEAR_PED_LAST_DAMAGE_BONE(fighter.ped);
            debugActionState(fighter, "boss-elite-duel-dash-started");
            return true;
        }
    }

    if (mobileDodge)
    {
        AI::TASK_GO_TO_COORD_WHILE_AIMING_AT_ENTITY(
            fighter.ped,
            evadeTo.x,
            evadeTo.y,
            evadeTo.z,
            target,
            6.35f,
            true,
            0.45f,
            1.6f,
            true,
            0,
            true,
            joaat("FIRING_PATTERN_FULL_AUTO"),
            0,
            0);
    }
    else
    {
        AI::TASK_PED_SLIDE_TO_COORD(
            fighter.ped,
            evadeTo.x,
            evadeTo.y,
            evadeTo.z,
            headingToward(evadeTo, targetPos),
            420.0f);
    }

    fighter.scriptedActionType = ScriptedActionType::BossEvasion;
    fighter.scriptedActionStartedAt = t;
    fighter.scriptedActionResumeAt = t + (mobileDodge ? kMobileBossDashMs : kSlideBossDodgeMs);
    fighter.scriptedActionTimeoutAt = fighter.scriptedActionResumeAt + 600u;
    fighter.evasionStartPos = self;
    fighter.evasionTargetPos = evadeTo;
    fighter.evasionStyle = mobileDodge ? BossEvasionStyle::MoveAndShootDash : BossEvasionStyle::Slide;
    fighter.evasionTaskRequested = true;
    fighter.evasionActuallyStarted = false;
    fighter.evasionFinished = false;
    fighter.evasionPlayerTriggered = false;
    fighter.evasionShootDuringDash = true;
    fighter.evasionVelocityFallbackApplied = false;
    fighter.evasionFallbackAttempts = 0;
    fighter.evasionThreat = target;
    fighter.evasionAimTarget = target;
    fighter.evasionFiringTarget = target;
    fighter.evasionRequestedAt = t;
    fighter.evasionStartedAt = 0;
    fighter.evasionExpectedEndAt = fighter.scriptedActionResumeAt;
    fighter.evasionDeadEyeBlockStartedAt = 0;
    fighter.evasionDeadEyeBlockUntil = 0;
    fighter.evasionFollowUpAt = fighter.scriptedActionResumeAt;
    fighter.evasionDeadEyeSuppressed = false;
    fighter.evasionShotsObserved = false;
    fighter.evasionSideX = sideX;
    fighter.evasionSideY = sideY;
    fighter.evasionBackX = backX;
    fighter.evasionBackY = backY;
    fighter.evasionSideSign = sideSign;
    fighter.evasionTaskSpeed = mobileDodge ? 6.35f : 0.0f;
    fighter.evasionDashDurationMs = mobileDodge ? kMobileBossDashMs : kSlideBossDodgeMs;
    fighter.lastEvasiveTask = t;
    fighter.lastRepositionTask = t;
    fighter.lastTask = t;
    fighter.nextPlayerAimDodgeAllowedAt = t + bossEvasiveCooldown(fighter);
    ENTITY::CLEAR_ENTITY_LAST_DAMAGE_ENTITY(fighter.ped);
    PED::CLEAR_PED_LAST_DAMAGE_BONE(fighter.ped);
    debugActionState(fighter, mobileDodge ? "boss-mobile-evasion-started" : "boss-slide-evasion-started");
    return true;
}

bool tryJohnArthurPlayerThreatEvasion(Fighter& fighter, Ped currentTarget, DWORD t)
{
    if (!isMobileFireBoss(fighter) ||
        g_menu.battleType != BattleType::AllWeapons ||
        protectedScriptedActionActive(fighter) ||
        weaponControllerSettling(fighter, t))
    {
        return false;
    }

    bool directlyAiming = false;
    bool recentlyDamagedByPlayer = false;
    if (!playerIsActivelyThreateningBoss(fighter, t, directlyAiming, recentlyDamagedByPlayer))
        return false;

    if (fighter.lastPlayerDodgeEligibilityCheck != 0 &&
        t - fighter.lastPlayerDodgeEligibilityCheck < kPlayerDodgeEligibilityCheckMs)
    {
        return false;
    }
    fighter.lastPlayerDodgeEligibilityCheck = t;

    bool aimPressureReady =
        directlyAiming &&
        fighter.playerAimPressureStartedAt != 0 &&
        t - fighter.playerAimPressureStartedAt >= kPlayerAimPressureMinMs &&
        t >= fighter.nextPlayerThreatDodgeAt;
    bool damagePressureReady =
        recentlyDamagedByPlayer &&
        (fighter.lastPlayerThreatDodgeAt == 0 ||
         t - fighter.lastPlayerThreatDodgeAt >= kPlayerDamageDodgeMinimumGapMs) &&
        (fighter.lastPlayerDamageDodgeAt == 0 ||
         t - fighter.lastPlayerDamageDodgeAt >= kPlayerDamageDodgeMinimumGapMs);
    if (!aimPressureReady && !damagePressureReady)
        return false;

    Ped player = playerPed();
    if (!exists(player))
        return false;

    Vec3 self = entityCoords(fighter.ped);
    Vec3 playerPos = entityCoords(player);
    float distToPlayer = distanceSquared(self, playerPos);
    if (distToPlayer < 5.0f * 5.0f || distToPlayer > 90.0f * 90.0f)
        return false;

    bool canSeePlayer =
        PED::CAN_PED_IN_COMBAT_SEE_TARGET(fighter.ped, player) ||
        ENTITY::HAS_ENTITY_CLEAR_LOS_TO_ENTITY(fighter.ped, player, 17);
    if (!canSeePlayer)
        return false;

    bool playerIsEnemy = canPlayerThreatBossDodgeUsePlayerAsTarget(fighter);
    Ped firingTarget = playerIsEnemy ? player : (isValidEnemyTarget(fighter, currentTarget) ? currentTarget : 0);
    Ped aimTarget = exists(firingTarget) ? firingTarget : player;
    bool shootDuringDash = exists(firingTarget);

    BossDashCandidate destination{};
    if (!chooseBossDashDestination(self, playerPos, true, 0.0f, false, destination) &&
        !chooseBossDashDestination(self, playerPos, true, 0.0f, true, destination))
    {
        return false;
    }

    fighter.evasionFallbackAttempts = 0;
    if (!issueBossMoveAndShootDash(
            fighter,
            player,
            aimTarget,
            firingTarget,
            shootDuringDash,
            destination,
            t,
            true))
    {
        return false;
    }

    fighter.lastPlayerThreatDodgeAt = t;
    fighter.nextPlayerThreatDodgeAt = t + playerThreatDodgeCooldown(fighter);
    fighter.nextPlayerAimDodgeAllowedAt = fighter.nextPlayerThreatDodgeAt;
    if (recentlyDamagedByPlayer)
        fighter.lastPlayerDamageDodgeAt = t;

    ENTITY::CLEAR_ENTITY_LAST_DAMAGE_ENTITY(fighter.ped);
    PED::CLEAR_PED_LAST_DAMAGE_BONE(fighter.ped);
    debugActionState(fighter, "boss-player-threat-evasion-requested");
    return true;
}

bool tryBossCrouchStrafe(Fighter& fighter, Ped target, DWORD t, float dist, bool canSeeTarget, bool inCover)
{
    if (fighter.difficulty != Difficulty::Bosses ||
        g_menu.battleType != BattleType::AllWeapons ||
        !exists(target) ||
        inCover ||
        !canSeeTarget ||
        t - fighter.lastDefensiveTask < 5200u ||
        t - fighter.lastRepositionTask < 950u ||
        fighter.bossBurstsSinceMovement < 2 ||
        dist < 9.0f * 9.0f ||
        dist > 54.0f * 54.0f ||
        (fighter.boss == kBossDutch && randomRange(0, 100) > 22) ||
        (fighter.boss == kBossColm && randomRange(0, 100) > 10) ||
        randomRange(0, 100) > 28)
    {
        return false;
    }

    Vec3 self = entityCoords(fighter.ped);
    Vec3 targetPos = entityCoords(target);
    float dx = targetPos.x - self.x;
    float dy = targetPos.y - self.y;
    float len = std::sqrt(std::max(0.001f, dx * dx + dy * dy));
    float sideSign = randomRange(0, 1) == 0 ? -1.0f : 1.0f;
    float sideX = (-dy / len) * sideSign;
    float sideY = (dx / len) * sideSign;
    float forwardX = dx / len;
    float forwardY = dy / len;
    float forwardDistance = dist > 26.0f * 26.0f ? 5.0f : -2.5f;

    Vec3 moveTo{
        self.x + sideX * 7.5f + forwardX * forwardDistance,
        self.y + sideY * 7.5f + forwardY * forwardDistance,
        self.z
    };
    snapToGround(moveTo);

    AI::CLEAR_PED_TASKS(fighter.ped, true, false);
    setPedCrouchMovement(fighter.ped, true);
    fighter.crouchUntil = t + 1700u;
    readyWeapon(fighter, t, true);
    PED::REGISTER_TARGET(fighter.ped, target, true);
    AI::TASK_GO_TO_COORD_WHILE_AIMING_AT_ENTITY(
        fighter.ped,
        moveTo.x,
        moveTo.y,
        moveTo.z,
        target,
        1.75f,
        true,
        1.0f,
        2.0f,
        true,
        0,
        true,
        joaat("FIRING_PATTERN_FULL_AUTO"),
        0,
        0);
    fighter.lastDefensiveTask = t;
    fighter.lastRepositionTask = t;
    fighter.bossBurstsSinceMovement = 0;
    fighter.lastTask = t;
    scheduleScriptedCombatResume(fighter, t, 1800u);
    return true;
}

bool updateBossWeaponForRange(Fighter& fighter, Ped target, DWORD t, float dist)
{
    if (fighter.difficulty != Difficulty::Bosses ||
        g_menu.battleType != BattleType::AllWeapons ||
        !exists(target) ||
        protectedScriptedActionActive(fighter))
    {
        return false;
    }

    Hash desired = fighter.mediumWeapon ? fighter.mediumWeapon : fighter.combatWeapon;
    float closeThreshold = 17.0f;
    float longThreshold = 55.0f;
    if (fighter.boss == kBossMicah)
    {
        closeThreshold = 999.0f;
        longThreshold = 999.0f;
    }
    else if (fighter.boss == kBossDutch)
    {
        closeThreshold = 12.0f;
        longThreshold = 28.0f;
    }
    else if (fighter.boss == kBossColm)
    {
        closeThreshold = 14.0f;
        longThreshold = 46.0f;
    }
    else if (fighter.boss == kBossJohn || fighter.boss == kBossArthur)
    {
        closeThreshold = 28.0f;
        longThreshold = 55.0f;
    }

    float meters = std::sqrt(std::max(0.0f, dist));
    if (shouldPollManagedWeapon(fighter, t))
    confirmManagedWeaponIfEquipped(fighter, t);
    if (hasTemporaryWeaponOverride(fighter, t))
        return false;

    float closeEnter = std::max(2.0f, closeThreshold - 2.0f);
    float closeExit = closeThreshold + 6.0f;
    float longEnter = longThreshold + 5.0f;
    float longExit = std::max(closeExit + 2.0f, longThreshold - 8.0f);

    Hash visibleWeapon = currentNormalWeapon(fighter);
    if (!visibleWeapon)
        visibleWeapon = isNormalWeaponForFighter(fighter, fighter.confirmedWeapon) ? fighter.confirmedWeapon : fighter.combatWeapon;

    if (visibleWeapon == fighter.closeWeapon && fighter.closeWeapon && meters < closeExit)
    {
        desired = fighter.closeWeapon;
    }
    else if (visibleWeapon == fighter.longWeapon && fighter.longWeapon && meters > longExit)
    {
        desired = fighter.longWeapon;
    }
    else if (meters < closeEnter && fighter.closeWeapon)
    {
        desired = fighter.closeWeapon;
    }
    else if (meters > longEnter && fighter.longWeapon)
    {
        desired = fighter.longWeapon;
    }

    if (!desired || desired == visibleWeapon)
    {
        if (desired)
            fighter.combatWeapon = desired;
        fighter.rangeWeaponCandidate = 0;
        fighter.rangeWeaponCandidateTarget = 0;
        fighter.rangeWeaponCandidateSince = 0;
        if (fighter.combatWeapon)
            fillWeaponAmmo(fighter.ped, fighter.combatWeapon);
        return false;
    }

    if (fighter.rangeWeaponCandidate != desired || fighter.rangeWeaponCandidateTarget != target)
    {
        fighter.rangeWeaponCandidate = desired;
        fighter.rangeWeaponCandidateTarget = target;
        fighter.rangeWeaponCandidateSince = t;
        return false;
    }

    if (t - fighter.rangeWeaponCandidateSince < kWeaponStableRangeMs ||
        t - fighter.lastShotTask < 700u)
        return false;

    bool requested = requestManagedWeapon(fighter, desired, t, false, "range");
    if (requested)
    {
        fighter.rangeWeaponCandidate = 0;
        fighter.rangeWeaponCandidateTarget = 0;
        fighter.rangeWeaponCandidateSince = 0;
    }
    return requested;
}

bool updateSpecialWeaponForRange(Fighter& fighter, Ped target, DWORD t, float dist)
{
    if (fighter.difficulty != Difficulty::Special ||
        g_menu.battleType != BattleType::AllWeapons ||
        !exists(target) ||
        protectedScriptedActionActive(fighter))
    {
        return false;
    }

    if (fighter.special == kSpecialTommy &&
        t - fighter.lastSpecialTask < 1450u &&
        dist < 24.0f * 24.0f)
    {
        WEAPON::SET_CURRENT_PED_WEAPON(fighter.ped, joaat("WEAPON_UNARMED"), true, 0, false, false);
        return false;
    }

    Hash desired = fighter.combatWeapon;
    if (fighter.special == kSpecialTommy)
    {
        if (dist < 13.0f * 13.0f && fighter.closeWeapon)
            desired = fighter.closeWeapon;
        else if (dist < 34.0f * 34.0f && fighter.mediumWeapon)
            desired = fighter.mediumWeapon;
        else if (fighter.longWeapon)
            desired = fighter.longWeapon;
    }
    else if (fighter.special == kSpecialCharles)
    {
        if (fighter.longWeapon && (fighter.combatWeapon == fighter.longWeapon || t - fighter.lastSpecialTask > 1300u))
            desired = fighter.longWeapon;
    }

    if (!desired || desired == fighter.combatWeapon)
    {
        if (fighter.combatWeapon)
            fillWeaponAmmo(fighter.ped, fighter.combatWeapon);
        return false;
    }

    fighter.combatWeapon = desired;
    readyWeapon(fighter, t, true);
    return true;
}

bool isEnemyFighterForBossTactic(const Fighter& fighter, const Fighter& other)
{
    if (other.ped == fighter.ped || !isAlive(other))
        return false;

    if (freeForAllActive())
        return !fighter.group || !other.group || fighter.group != other.group;

    return other.team != fighter.team;
}

bool hasFriendlyInDynamiteRadius(const Fighter& fighter, Vec3 center)
{
    float radiusSq = (kBossDynamiteClusterRadius + 2.5f) * (kBossDynamiteClusterRadius + 2.5f);
    for (const Fighter& other : g_runtime.fighters)
    {
        if (other.ped == fighter.ped || !isAlive(other) || isEnemyFighterForBossTactic(fighter, other))
            continue;

        if (distanceSquared(center, entityCoords(other.ped)) <= radiusSq)
            return true;
    }

    return false;
}

bool findBossDynamiteCluster(const Fighter& fighter, Vec3& targetPos, int& targetCount)
{
    struct Candidate
    {
        const Fighter* fighter{};
        Vec3 pos{};
        bool enemy = false;
    };

    targetCount = 0;
    Vec3 self = entityCoords(fighter.ped);
    Ped player = playerPed();
    bool playerExists = exists(player) && !PED::IS_PED_DEAD_OR_DYING(player, true);
    Vec3 playerPos = playerExists ? entityCoords(player) : Vec3{};
    float clusterRadiusSq = kBossDynamiteClusterRadius * kBossDynamiteClusterRadius;
    float minThrowSq = kBossDynamiteMinThrowDistance * kBossDynamiteMinThrowDistance;
    float maxThrowSq = kBossDynamiteMaxThrowDistance * kBossDynamiteMaxThrowDistance;
    float playerSafetySq = kBossDynamitePlayerSafetyRadius * kBossDynamitePlayerSafetyRadius;
    float bestDistanceSq = 99999999.0f;

    std::vector<Candidate> candidates;
    candidates.reserve(g_runtime.fighters.size());
    for (const Fighter& centerFighter : g_runtime.fighters)
    {
        if (centerFighter.ped == fighter.ped || !isAlive(centerFighter))
            continue;

        candidates.push_back({ &centerFighter, entityCoords(centerFighter.ped), isEnemyFighterForBossTactic(fighter, centerFighter) });
    }

    for (const Candidate& centerCandidate : candidates)
    {
        if (!centerCandidate.enemy)
            continue;

        Vec3 center = centerCandidate.pos;
        float throwDistSq = distanceSquared(self, center);
        if (throwDistSq < minThrowSq || throwDistSq > maxThrowSq)
            continue;

        bool canSeeCenter =
            PED::CAN_PED_IN_COMBAT_SEE_TARGET(fighter.ped, centerCandidate.fighter->ped) ||
            ENTITY::HAS_ENTITY_CLEAR_LOS_TO_ENTITY(fighter.ped, centerCandidate.fighter->ped, 17);
        if (!canSeeCenter)
            continue;

        if (playerExists && distanceSquared(center, playerPos) < playerSafetySq)
            continue;

        bool friendlyInRadius = false;
        float friendlyRadiusSq = (kBossDynamiteClusterRadius + 2.5f) * (kBossDynamiteClusterRadius + 2.5f);
        for (const Candidate& possibleFriendly : candidates)
        {
            if (!possibleFriendly.enemy && distanceSquared(center, possibleFriendly.pos) <= friendlyRadiusSq)
            {
                friendlyInRadius = true;
                break;
            }
        }
        if (friendlyInRadius)
            continue;

        int count = 0;
        for (const Candidate& possibleTarget : candidates)
        {
            if (!possibleTarget.enemy)
                continue;

            if (distanceSquared(center, possibleTarget.pos) <= clusterRadiusSq)
                ++count;
        }

        if (count > targetCount || (count == targetCount && throwDistSq < bestDistanceSq))
        {
            targetCount = count;
            targetPos = center;
            bestDistanceSq = throwDistSq;
        }
    }

    return targetCount >= kBossDynamiteMinClusterTargets;
}

bool dynamiteThrowAlreadyActive()
{
    Hash dynamite = joaat("WEAPON_THROWN_DYNAMITE");
    for (const Fighter& fighter : g_runtime.fighters)
    {
        if (fighter.scriptedActionType == ScriptedActionType::DynamiteThrow &&
            fighter.projectileWeapon == dynamite)
        {
            return true;
        }
    }
    return false;
}

bool tryBossDynamite(Fighter& fighter, Ped target, DWORD t)
{
    if (fighter.difficulty != Difficulty::Bosses ||
        g_menu.battleType != BattleType::AllWeapons ||
        !exists(target) ||
        protectedScriptedActionActive(fighter) ||
        t < fighter.nextDynamiteScanAt ||
        t < fighter.projectileFailureCooldownUntil ||
        t - fighter.spawnedAt < 8000u ||
        t - fighter.lastDynamiteTask < kBossDynamiteCooldownMs ||
        t - fighter.lastEvasiveTask < 2200u ||
        randomRange(0, 100) > 22)
    {
        return false;
    }

    fighter.nextDynamiteScanAt = t + kDynamiteScanBaseMs + static_cast<DWORD>(randomRange(0, 700));
    if (dynamiteThrowAlreadyActive())
        return false;

    Vec3 throwPos{};
    int targetCount{};
    if (!findBossDynamiteCluster(fighter, throwPos, targetCount))
    {
        fighter.nextDynamiteScanAt = t + 2200u + static_cast<DWORD>(randomRange(0, 900));
        return false;
    }

    Hash dynamite = joaat("WEAPON_THROWN_DYNAMITE");
    throwPos.z += 0.35f;
    return startProjectileThrowAction(
        fighter,
        target,
        t,
        dynamite,
        throwPos,
        projectileRestoreWeaponForFighter(fighter),
        3,
        "dynamite-equip");
}

void applyHitDamageBonuses(Fighter& victim, DWORD t, int& health)
{
    if (!exists(victim.ped) || health <= 0 || health >= victim.lastHealth)
    {
        return;
    }

    int damageTaken = victim.lastHealth - health;
    for (const Fighter& attacker : g_runtime.fighters)
    {
        if (attacker.ped == victim.ped ||
            !isAlive(attacker) ||
            !isEnemyFighterForBossTactic(attacker, victim) ||
            !ENTITY::HAS_ENTITY_BEEN_DAMAGED_BY_ENTITY(victim.ped, attacker.ped, true, true))
        {
            continue;
        }

        bool dutchBonus = attacker.difficulty == Difficulty::Bosses && attacker.boss == kBossDutch;
        bool billBonus = attacker.difficulty == Difficulty::Special && attacker.special == kSpecialBill;
        if (!dutchBonus && !billBonus)
            continue;

        bool braced =
            PED::IS_PED_IN_COVER(attacker.ped, false, false) ||
            PED::IS_PED_AIMING_FROM_COVER(attacker.ped) ||
            PED::IS_PED_SHOOTING(attacker.ped) ||
            AI::IS_PED_STILL(attacker.ped) ||
            PED::IS_PED_STOPPED(attacker.ped);
        int bonus = dutchBonus
            ? std::clamp((damageTaken * (braced ? 75 : 50)) / 100, braced ? 12 : 8, braced ? 36 : 28)
            : std::clamp((damageTaken * 25) / 100, 4, 16);
        int applied = std::min(bonus, std::max(0, health - 8));
        if (applied <= 0)
            return;

        health -= applied;
        ENTITY::SET_ENTITY_HEALTH(victim.ped, health, 0);
        victim.lastDamage = t;
        ENTITY::CLEAR_ENTITY_LAST_DAMAGE_ENTITY(victim.ped);
        return;
    }
}

bool tryBossAggressionFallback(
    Fighter& fighter,
    Ped target,
    DWORD t,
    float dist,
    float preferredRange,
    float burstRange,
    bool canSeeTarget,
    bool inCover,
    bool woundedBoss)
{
    if (fighter.difficulty != Difficulty::Bosses ||
        g_menu.battleType != BattleType::AllWeapons ||
        woundedBoss ||
        !exists(target))
    {
        return false;
    }

    bool taskQuiet =
        t - fighter.lastShotTask > kBossAggressionFallbackMs &&
        t - fighter.lastRepositionTask > kBossAggressionFallbackMs;
    bool notActivelyFighting = PED::IS_PED_IN_COMBAT(fighter.ped, target) == 0;
    bool blockedTarget = !canSeeTarget && t - fighter.lastRepositionTask > 2200u;
    if (!taskQuiet && !notActivelyFighting && !blockedTarget)
        return false;

    readyWeapon(fighter, t, true);
    PED::REGISTER_TARGET(fighter.ped, target, true);

    if (canSeeTarget && dist < burstRange * burstRange && t - fighter.lastShotTask > 850u)
    {
        taskBossAttackBurst(fighter, target, t, inCover, false);
        return true;
    }

    if (t - fighter.lastRepositionTask <= 1900u)
        return false;

    if (dist > preferredRange * preferredRange)
        return taskApproachTarget(fighter, target, t, true, canSeeTarget);

    if (isMobileFireBoss(fighter))
    {
        AI::TASK_COMBAT_PED(fighter.ped, target, 0, 16);
        fighter.lastTask = t;
        return true;
    }

    Vec3 self = entityCoords(fighter.ped);
    Vec3 targetPos = entityCoords(target);
    float dx = targetPos.x - self.x;
    float dy = targetPos.y - self.y;
    float len = std::sqrt(std::max(0.001f, dx * dx + dy * dy));
    float sideSign = randomRange(0, 1) == 0 ? -1.0f : 1.0f;
    float sideX = (-dy / len) * sideSign;
    float sideY = (dx / len) * sideSign;
    float forwardX = dx / len;
    float forwardY = dy / len;
    float sideDistance = canSeeTarget ? 5.5f : 9.0f;
    float forwardDistance = canSeeTarget ? 3.0f : 8.0f;

    Vec3 moveTo{
        self.x + sideX * sideDistance + forwardX * forwardDistance,
        self.y + sideY * sideDistance + forwardY * forwardDistance,
        self.z
    };
    snapToGround(moveTo);

    AI::TASK_GO_TO_COORD_WHILE_AIMING_AT_ENTITY(
        fighter.ped,
        moveTo.x,
        moveTo.y,
        moveTo.z,
        target,
        2.65f,
        true,
        1.0f,
        2.0f,
        true,
        0,
        true,
        joaat("FIRING_PATTERN_FULL_AUTO"),
        0,
        0);
    fighter.lastRepositionTask = t;
    fighter.lastTask = t;
    scheduleScriptedCombatResume(fighter, t, 1600u);
    return true;
}

bool tryTommyCharge(Fighter& fighter, Ped target, DWORD t, float dist)
{
    if (fighter.difficulty != Difficulty::Special ||
        fighter.special != kSpecialTommy ||
        !exists(target) ||
        dist > 62.0f * 62.0f)
    {
        return false;
    }

    bool closeGrappleRange = dist < 9.0f * 9.0f;
    DWORD tommyCooldown = closeGrappleRange ? 450u : 1200u;
    if (t - fighter.lastSpecialTask < tommyCooldown)
        return false;

    bool targetIsPlayer = target == playerPed();
    if (!targetIsPlayer && dist > 46.0f * 46.0f && randomRange(0, 100) > 88)
        return false;

    bool tackle = closeGrappleRange && randomRange(0, 100) < 96;
    bool chargingTackle = dist < 24.0f * 24.0f && randomRange(0, 100) < 86;
    Hash meleeWeapon = (tackle || chargingTackle) ? joaat("WEAPON_UNARMED") : (fighter.closeWeapon ? fighter.closeWeapon : joaat("WEAPON_UNARMED"));
    Vec3 self = entityCoords(fighter.ped);
    Vec3 targetPos = entityCoords(target);
    float dx = targetPos.x - self.x;
    float dy = targetPos.y - self.y;
    float len = std::sqrt(std::max(0.001f, dx * dx + dy * dy));

    AI::CLEAR_PED_TASKS(fighter.ped, true, false);
    setPedActionMode(fighter.ped, true);
    beginTemporaryWeaponOverride(fighter, meleeWeapon, t, closeGrappleRange ? 1200u : 2800u);
    WEAPON::SET_CURRENT_PED_WEAPON(fighter.ped, meleeWeapon, true, 0, false, false);
    PED::REGISTER_TARGET(fighter.ped, target, true);

    if (!closeGrappleRange)
    {
        ENTITY::SET_ENTITY_VELOCITY(fighter.ped, (dx / len) * 9.4f, (dy / len) * 9.4f, chargingTackle ? 0.55f : 0.35f);
        AI::TASK_GO_TO_ENTITY(fighter.ped, target, 2400, 0.75f, 5.8f, 0.0f, 0);
        if (dist < 20.0f * 20.0f)
            AI::TASK_PUT_PED_DIRECTLY_INTO_MELEE(fighter.ped, target, 0.0f, -1.0f, 0.0f, 0.0f, 0);
    }
    else
    {
        ENTITY::SET_ENTITY_VELOCITY(fighter.ped, (dx / len) * 3.8f, (dy / len) * 3.8f, 0.25f);
        AI::TASK_PUT_PED_DIRECTLY_INTO_MELEE(fighter.ped, target, 0.0f, -1.0f, 0.0f, 0.0f, 0);
        if ((tackle || chargingTackle) && t - fighter.lastGrappleAttempt > 650u)
        {
            fighter.lastGrappleAttempt = t;
            bool mounted = AI::_0x779A2FFACEFAEA7B(
                fighter.ped,
                target,
                joaat("AR_GRAPPLE_MOUNT_FROM_FRONT"),
                false,
                0.0f,
                false,
                0) != false;

            if (!mounted)
            {
                AI::_0xA05F3F20889D7A5B(
                    fighter.ped,
                    target,
                    joaat("AR_GRAPPLE_FRONT_FROM_FRONT"),
                    0.0f,
                    1.0f,
                    true,
                    0);
            }
        }
    }

    fighter.lastSpecialTask = t;
    fighter.lastRepositionTask = t;
    fighter.lastTask = t;
    scheduleScriptedCombatResume(fighter, t, closeGrappleRange ? 900u : 700u);
    return true;
}

bool tryCharlesAmbush(Fighter& fighter, Ped target, DWORD t, float dist, bool canSeeTarget)
{
    if (fighter.difficulty != Difficulty::Special ||
        fighter.special != kSpecialCharles ||
        g_menu.battleType != BattleType::AllWeapons ||
        !exists(target))
    {
        return false;
    }

    if (canSeeTarget && dist > 24.0f * 24.0f && dist < 86.0f * 86.0f && fighter.longWeapon && t - fighter.lastShotTask > 620u)
    {
        fighter.combatWeapon = fighter.longWeapon;
        readyWeapon(fighter, t, true);
        setPedCrouchMovement(fighter.ped, true);
        fighter.crouchUntil = t + 1450u;
        PED::REGISTER_TARGET(fighter.ped, target, true);
        AI::TASK_SHOOT_AT_ENTITY(fighter.ped, target, 1350, joaat("FIRING_PATTERN_FULL_AUTO"), true);
        fighter.lastShotTask = t;
        fighter.lastTask = t;
        scheduleScriptedCombatResume(fighter, t, 1500u);
        return true;
    }

    if (dist < 7.0f * 7.0f ||
        dist > 28.0f * 28.0f ||
        !canSeeTarget ||
        t - fighter.lastSpecialTask < 9000u ||
        t - fighter.lastShotTask < 1350u ||
        randomRange(0, 100) > 24)
    {
        return false;
    }

    Vec3 targetPos = entityCoords(target);

    Hash throwable = randomRange(0, 1) == 0 ?
        (fighter.closeWeapon ? fighter.closeWeapon : giveWeapon(fighter.ped, "WEAPON_THROWN_THROWING_KNIVES", false)) :
        (fighter.mediumWeapon ? fighter.mediumWeapon : giveWeapon(fighter.ped, "WEAPON_THROWN_TOMAHAWK", false));

    setPedCrouchMovement(fighter.ped, true);
    fighter.crouchUntil = t + 2200u;
    Vec3 throwPos{ targetPos.x, targetPos.y, targetPos.z + 0.25f };
    bool started = startProjectileThrowAction(
        fighter,
        target,
        t,
        throwable ? throwable : fighter.combatWeapon,
        throwPos,
        fighter.longWeapon ? fighter.longWeapon : projectileRestoreWeaponForFighter(fighter),
        3,
        "charles-throwable-equip");
    if (started)
    {
        fighter.lastSpecialTask = t;
        fighter.lastRepositionTask = t;
        fighter.lastTask = t;
    }
    return started;
}

bool tryJavierEvasiveBurst(Fighter& fighter, Ped target, DWORD t, float dist, bool canSeeTarget)
{
    bool eliteDuel = eliteNpcDuelTarget(fighter, target);
    DWORD evasionCooldown = eliteDuel ? 2100u : 3000u;
    float maxEvasionDistance = eliteDuel ? 78.0f : 66.0f;
    if (fighter.difficulty != Difficulty::Special ||
        fighter.special != kSpecialJavier ||
        g_menu.battleType != BattleType::AllWeapons ||
        !exists(target) ||
        t - fighter.lastEvasiveTask < evasionCooldown ||
        dist < 7.0f * 7.0f ||
        dist > maxEvasionDistance * maxEvasionDistance)
    {
        return false;
    }

    Ped player = playerPed();
    Player playerId = PLAYER::PLAYER_ID();
    bool playerPressure =
        target == player &&
        (PLAYER::IS_PLAYER_FREE_AIMING_AT_ENTITY(playerId, fighter.ped) ||
         PLAYER::IS_PLAYER_TARGETTING_ENTITY(playerId, fighter.ped, true));
    bool recentlyHit = t - fighter.lastDamage < 1500u || ENTITY::HAS_ENTITY_BEEN_DAMAGED_BY_ANY_PED(fighter.ped);
    bool shouldDodge =
        (playerPressure && randomRange(0, 100) < 62) ||
        (recentlyHit && randomRange(0, 100) < (eliteDuel ? 62 : 45)) ||
        (canSeeTarget && randomRange(0, 100) < (eliteDuel ? 28 : 14));
    if (!shouldDodge)
        return false;

    Vec3 self = entityCoords(fighter.ped);
    Vec3 targetPos = entityCoords(target);
    float dx = targetPos.x - self.x;
    float dy = targetPos.y - self.y;
    float len = std::sqrt(std::max(0.001f, dx * dx + dy * dy));
    float sideSign = randomRange(0, 1) == 0 ? -1.0f : 1.0f;
    float sideX = (-dy / len) * sideSign;
    float sideY = (dx / len) * sideSign;
    bool slideDive = randomRange(0, 100) < (eliteDuel ? 58 : 44);
    Vec3 evadeTo{
        self.x + sideX * (slideDive ? 17.0f : 11.0f) - (dx / len) * 1.8f,
        self.y + sideY * (slideDive ? 17.0f : 11.0f) - (dy / len) * 1.8f,
        self.z
    };
    snapToGround(evadeTo);

    AI::CLEAR_PED_TASKS(fighter.ped, true, false);
    readyWeapon(fighter, t, true);
    PED::REGISTER_TARGET(fighter.ped, target, true);
    setPedCrouchMovement(fighter.ped, slideDive);
    fighter.crouchUntil = slideDive ? t + 950u : 0;

    if (slideDive)
    {
        AI::TASK_PED_SLIDE_TO_COORD(
            fighter.ped,
            evadeTo.x,
            evadeTo.y,
            evadeTo.z,
            headingToward(evadeTo, targetPos),
            360.0f);
    }
    else
    {
        AI::TASK_GO_TO_COORD_WHILE_AIMING_AT_ENTITY(
            fighter.ped,
            evadeTo.x,
            evadeTo.y,
            evadeTo.z,
            target,
            eliteDuel ? 3.55f : 2.9f,
            true,
            1.0f,
            2.0f,
            true,
            0,
            true,
            joaat("FIRING_PATTERN_FULL_AUTO"),
            0,
            0);
    }

    fighter.lastEvasiveTask = t;
    fighter.lastRepositionTask = t;
    fighter.lastShotTask = slideDive ? t - 360u : t - 220u;
    fighter.lastTask = t;
    scheduleScriptedCombatResume(fighter, t, slideDive ? 650u : 1500u);
    ENTITY::CLEAR_ENTITY_LAST_DAMAGE_ENTITY(fighter.ped);
    PED::CLEAR_PED_LAST_DAMAGE_BONE(fighter.ped);
    return true;
}

bool trySpecialCombatBehavior(Fighter& fighter, Ped target, DWORD t, float dist, bool canSeeTarget)
{
    if (tryJavierEvasiveBurst(fighter, target, t, dist, canSeeTarget))
        return true;

    if (tryTommyCharge(fighter, target, t, dist))
        return true;

    if (tryCharlesAmbush(fighter, target, t, dist, canSeeTarget))
        return true;

    return false;
}

void applyAdvancedCombatNudges(Fighter& fighter, Ped target, DWORD t)
{
    if (g_menu.battleType != BattleType::AllWeapons || !isEnhancedFighter(fighter) || !exists(target))
        return;
    if (protectedScriptedActionActive(fighter))
        return;

    float dist = distanceSquared(entityCoords(fighter.ped), entityCoords(target));
    float preferredRange = preferredGunRangeForFighter(fighter);
    if (fighter.difficulty == Difficulty::Extreme)
    {
        if (t - fighter.lastRepositionTask < 3400u || dist <= (preferredRange + 14.0f) * (preferredRange + 14.0f))
            return;

        bool canSeeTarget =
            PED::CAN_PED_IN_COMBAT_SEE_TARGET(fighter.ped, target) ||
            ENTITY::HAS_ENTITY_CLEAR_LOS_TO_ENTITY(fighter.ped, target, 17);
        if (!taskPursueDistantTarget(fighter, target, t, dist, false))
            taskApproachTarget(fighter, target, t, false, canSeeTarget);
        return;
    }

    bool boss = fighter.difficulty == Difficulty::Bosses;
    float burstRange = preferredRange + (boss ? bossBurstRangeBonus(fighter) : (isAdvancedFighter(fighter) ? 8.0f : 4.0f));
    int health = ENTITY::GET_ENTITY_HEALTH(fighter.ped);
    bool woundedBoss = isLowHealthBoss(fighter, health);
    bool inCover =
        PED::IS_PED_IN_COVER(fighter.ped, false, false) ||
        PED::IS_PED_AIMING_FROM_COVER(fighter.ped) ||
        PED::IS_PED_GOING_INTO_COVER(fighter.ped);
    bool canSeeTarget =
        PED::CAN_PED_IN_COMBAT_SEE_TARGET(fighter.ped, target) ||
        ENTITY::HAS_ENTITY_CLEAR_LOS_TO_ENTITY(fighter.ped, target, 17);

    confirmManagedWeaponIfEquipped(fighter, t);
    if (weaponControllerSettling(fighter, t) && !bossUnderSustainedFire(fighter, t))
        return;

    DWORD nativeCoverSearchMs = 2800u;
    bool allowingNativeCoverSearch = boss &&
        !inCover &&
        fighter.defensiveCombatStartedAt != 0 &&
        fighter.defensiveCombatUntil > t &&
        t - fighter.defensiveCombatStartedAt < nativeCoverSearchMs;
    if (allowingNativeCoverSearch)
        return;

    bool bossSwitchedWeapon = updateBossWeaponForRange(fighter, target, t, dist);
    if (bossSwitchedWeapon)
    {
        PED::REGISTER_TARGET(fighter.ped, target, true);
        scheduleScriptedCombatResume(fighter, t, kWeaponSettleMs);
        return;
    }
    else if (updateSpecialWeaponForRange(fighter, target, t, dist))
    {
        scheduleScriptedCombatResume(fighter, t, 800u);
        return;
    }

    if (woundedBoss)
    {
        if (!inCover && dist < 32.0f * 32.0f && t - fighter.lastDefensiveTask > 6000u)
        {
            AI::CLEAR_PED_TASKS(fighter.ped, true, false);
            AI::TASK_SMART_FLEE_PED(fighter.ped, target, 22.0f, 1200, false, false, 0);
            fighter.lastDefensiveTask = t;
            fighter.lastTask = t;
            scheduleScriptedCombatResume(fighter, t, 1350u);
            return;
        }
    }

    if (trySpecialCombatBehavior(fighter, target, t, dist, canSeeTarget))
        return;

    if (tryBossDynamite(fighter, target, t))
        return;

    if (boss && tryBossNativeCover(fighter, target, t, dist, canSeeTarget, woundedBoss))
        return;

    if (!inCover && dist > burstRange * burstRange)
    {
        DWORD settleDelay = isAdvancedFighter(fighter) ? 1450u : 2100u;
        if (t - fighter.lastRepositionTask < settleDelay)
            return;

        if (!taskPursueDistantTarget(fighter, target, t, dist, false))
            taskApproachTarget(fighter, target, t, false, canSeeTarget);
        return;
    }

    bool allowLegacyBossEvasion = false;
    if (boss && tryBossNativeRepositionRun(fighter, target, t, dist, canSeeTarget))
        return;

    if (boss &&
        allowLegacyBossEvasion &&
        isMobileFireBoss(fighter) &&
        !inCover &&
        !weaponControllerSettling(fighter, t) &&
        tryBossEvasiveBurst(fighter, target, t, dist, canSeeTarget))
    {
        return;
    }

    if (boss &&
        fighter.boss == kBossMicah &&
        canSeeTarget &&
        dist < burstRange * burstRange &&
        t - fighter.lastShotTask > shootBurstDelay(fighter))
    {
        taskBossAttackBurst(fighter, target, t, inCover, woundedBoss);
        return;
    }

    if (boss &&
        t - fighter.lastEvasiveTask > 420u &&
        t - fighter.lastEvasiveTask < 1900u &&
        canSeeTarget &&
        dist < burstRange * burstRange &&
        t - fighter.lastShotTask > (fighter.boss == kBossMicah ? 180u : (fighter.boss == kBossJohn || fighter.boss == kBossArthur ? 130u : 360u)))
    {
        taskBossAttackBurst(fighter, target, t, inCover, woundedBoss);
        return;
    }

    if (boss &&
        allowLegacyBossEvasion &&
        eliteNpcDuelTarget(fighter, target) &&
        !isMobileFireBoss(fighter) &&
        (!inCover || bossUnderSustainedFire(fighter, t)) &&
        tryBossEvasiveBurst(fighter, target, t, dist, canSeeTarget))
    {
        return;
    }

    DWORD aggressiveBurstDelay = inCover ? (woundedBoss ? 900u : 500u) : shootBurstDelay(fighter);
    if (boss &&
        fighter.bossBurstsSinceMovement < bossMinimumBurstsBeforeMovement(fighter) &&
        canSeeTarget &&
        dist < burstRange * burstRange &&
        t - fighter.lastShotTask > aggressiveBurstDelay)
    {
        taskBossAttackBurst(fighter, target, t, inCover, woundedBoss);
        return;
    }

    if (boss &&
        allowLegacyBossEvasion &&
        !isMobileFireBoss(fighter) &&
        (!inCover || bossUnderSustainedFire(fighter, t)) &&
        tryBossEvasiveBurst(fighter, target, t, dist, canSeeTarget))
        return;

    if (boss &&
        canSeeTarget &&
        dist < burstRange * burstRange &&
        t - fighter.lastShotTask > aggressiveBurstDelay)
    {
        taskBossAttackBurst(fighter, target, t, inCover, woundedBoss);
        return;
    }

    if (!boss && !inCover && taskStrafeTarget(fighter, target, t, dist, canSeeTarget))
        return;

    bool shouldForceCoverShot = boss && inCover && dist < burstRange * burstRange;
    DWORD burstDelay = shouldForceCoverShot ? (woundedBoss ? 900u : 500u) : shootBurstDelay(fighter);
    if ((canSeeTarget || shouldForceCoverShot) && dist < burstRange * burstRange && t - fighter.lastShotTask > burstDelay)
    {
        if (boss)
        {
            taskBossAttackBurst(fighter, target, t, inCover, woundedBoss);
        }
        else
        {
            readyWeapon(fighter, t, true);
            PED::REGISTER_TARGET(fighter.ped, target, true);
            AI::TASK_SHOOT_AT_ENTITY(fighter.ped, target, 900, joaat("FIRING_PATTERN_FULL_AUTO"), true);
            AI::TASK_COMBAT_PED(fighter.ped, target, 0, 16);
            fighter.lastShotTask = t;
            fighter.lastTask = t;
        }
        return;
    }

    if (tryBossAggressionFallback(fighter, target, t, dist, preferredRange, burstRange, canSeeTarget, inCover, woundedBoss))
        return;
}

bool tryBossGrapple(Fighter& fighter, Ped target, DWORD t, float dist)
{
    bool specialGrappler =
        fighter.difficulty == Difficulty::Special &&
        kSpecialPeds[static_cast<size_t>(fighter.special)].meleeSpecialist;

    if ((fighter.difficulty != Difficulty::Bosses && !specialGrappler) ||
        g_menu.battleType != BattleType::NoWeapons ||
        !exists(fighter.ped) ||
        !exists(target) ||
        dist > 2.6f * 2.6f ||
        t - fighter.lastGrappleAttempt < (specialGrappler ? 4300u : 5600u) ||
        PED::IS_PED_DEAD_OR_DYING(target, true) ||
        PED::IS_PED_RAGDOLL(target) ||
        PED::IS_PED_RUNNING_RAGDOLL_TASK(target))
    {
        return false;
    }

    fighter.lastGrappleAttempt = t;
    setPedActionMode(fighter.ped, true);
    beginTemporaryWeaponOverride(fighter, joaat("WEAPON_UNARMED"), t, 1800u);
    WEAPON::SET_CURRENT_PED_WEAPON(fighter.ped, joaat("WEAPON_UNARMED"), true, 0, false, false);
    PED::REGISTER_TARGET(fighter.ped, target, true);
    AI::TASK_PUT_PED_DIRECTLY_INTO_MELEE(fighter.ped, target, 0.0f, -1.0f, 0.0f, 0.0f, 0);

    bool mounted = AI::_0x779A2FFACEFAEA7B(
        fighter.ped,
        target,
        joaat("AR_GRAPPLE_MOUNT_FROM_FRONT"),
        false,
        0.0f,
        false,
        0) != false;

    if (!mounted)
    {
        AI::_0xA05F3F20889D7A5B(
            fighter.ped,
            target,
            joaat("AR_GRAPPLE_FRONT_FROM_FRONT"),
            0.0f,
            1.0f,
            true,
            0);
    }

    fighter.lastTask = t;
    return true;
}

bool attackerIsBehindPed(Ped victim, Ped attacker)
{
    if (!exists(victim) || !exists(attacker))
        return false;

    Vec3 victimPos = entityCoords(victim);
    Vec3 attackerPos = entityCoords(attacker);
    float dx = attackerPos.x - victimPos.x;
    float dy = attackerPos.y - victimPos.y;
    float distSq = dx * dx + dy * dy;
    if (distSq > 3.0f * 3.0f || distSq < 0.01f)
        return false;

    float heading = ENTITY::GET_ENTITY_HEADING(victim) * (kPi / 180.0f);
    float forwardX = std::sin(heading);
    float forwardY = std::cos(heading);
    float dist = std::sqrt(distSq);
    float dot = (forwardX * dx + forwardY * dy) / dist;
    return dot < -0.35f;
}

bool attackerHasPedInMelee(Ped attacker, Ped victim)
{
    if (!exists(attacker) || !exists(victim))
        return false;

    return PED::GET_MELEE_TARGET_FOR_PED(attacker) == victim;
}

bool beginCinematicExecutionRecovery(Fighter& victim, DWORD t, int health, bool dead)
{
    if (!exists(victim.ped) || !shouldProtectCinematicKills(victim))
        return false;

    if (victim.cinematicRecoveryActive)
        return true;

    int threshold = executionHealthThreshold(victim);
    int baseHealth = std::clamp(health > 0 ? health : victim.lastHealth, 1, victim.maxHealth);
    if (threshold > 0 && baseHealth <= threshold)
        return false;

    if (!dead && !PED::IS_PED_BEING_STEALTH_KILLED(victim.ped))
        return false;

    victim.cinematicRecoveryActive = true;
    victim.cinematicRecoveryStarted = t;
    victim.cinematicRecoveryRecoverAt = t + kExecutionRecoveryMinMs;
    victim.cinematicRecoveryHealth = std::clamp(baseHealth - g_settings.bossBlockedExecutionDamage, 1, victim.maxHealth);
    victim.lastDamage = t;
    ENTITY::SET_ENTITY_INVINCIBLE(victim.ped, true);
    setFighterCriticalHitsAllowed(victim, false);
    recordProtectedExecutionFallback(victim, "cinematic-recovery-started", t);
    return true;
}

bool maintainCinematicExecutionRecovery(Fighter& fighter, DWORD t, int& health, bool& dead)
{
    if (!fighter.cinematicRecoveryActive)
        return false;

    if (!exists(fighter.ped))
    {
        fighter.cinematicRecoveryActive = false;
        return false;
    }

    ENTITY::SET_ENTITY_INVINCIBLE(fighter.ped, true);
    setFighterCriticalHitsAllowed(fighter, false);

    bool maxWaitExpired = t - fighter.cinematicRecoveryStarted >= kExecutionRecoveryMaxMs;
    bool minWaitExpired = t >= fighter.cinematicRecoveryRecoverAt;
    if (!maxWaitExpired && !minWaitExpired)
        return true;

    if (dead || PED::IS_PED_DEAD_OR_DYING(fighter.ped, true) || PED::IS_PED_FATALLY_INJURED(fighter.ped))
    {
        PED::RESURRECT_PED(fighter.ped);
        PED::REVIVE_INJURED_PED(fighter.ped);
    }

    AI::CLEAR_PED_TASKS(fighter.ped, true, false);
    PED::RESET_PED_RAGDOLL_TIMER(fighter.ped);
    int restored = std::clamp(fighter.cinematicRecoveryHealth, 1, fighter.maxHealth);
    fighter.cinematicRecoveryActive = false;
    fighter.cinematicRecoveryStarted = 0;
    fighter.cinematicRecoveryRecoverAt = 0;
    fighter.cinematicRecoveryHealth = 0;
    applyPedTuning(fighter);
    ENTITY::SET_ENTITY_HEALTH(fighter.ped, restored, 0);
    clearVisibleDamage(fighter.ped);
    applyExecutionThresholdProtection(fighter, restored, false);
    ENTITY::SET_ENTITY_INVINCIBLE(fighter.ped, false);
    ++fighter.criticalRevives;
    fighter.lastHealth = restored;
    fighter.lastDamage = t;
    fighter.lastTask = 0;
    fighter.currentTarget = 0;
    fighter.currentTargetStartedAt = 0;
    resetWeaponController(fighter);
    health = restored;
    dead = false;
    return true;
}

bool breakProtectedExecutionAttempt(Fighter& victim, DWORD t, bool executionState)
{
    if (!shouldProtectCinematicKills(victim) || !exists(victim.ped))
        return false;

    int currentHealth = ENTITY::GET_ENTITY_HEALTH(victim.ped);
    int threshold = executionHealthThreshold(victim);
    if ((currentHealth > 0 && currentHealth <= threshold) ||
        (currentHealth <= 0 && victim.lastHealth > 0 && victim.lastHealth <= threshold))
    {
        return false;
    }

    if (!executionState)
        return false;

    if (t - victim.lastGrappleBreak < 350)
        return false;

    bool broke = false;
    Ped closestAttacker{};
    float closestDistance = 999999.0f;

    auto breakAttacker = [&](Ped attacker) {
        if (!exists(attacker) || attacker == victim.ped || PED::IS_PED_DEAD_OR_DYING(attacker, true))
            return;

        float dist = distanceSquared(entityCoords(victim.ped), entityCoords(attacker));
        if (dist > 4.25f * 4.25f)
            return;

        bool likelyExecutionAttacker =
            attackerHasPedInMelee(attacker, victim.ped) ||
            attackerIsBehindPed(victim.ped, attacker) ||
            (PED::IS_PED_IN_MELEE_COMBAT(attacker) && dist < 3.2f * 3.2f) ||
            ENTITY::HAS_ENTITY_BEEN_DAMAGED_BY_ENTITY(victim.ped, attacker, true, true);

        if (!likelyExecutionAttacker)
        {
            if (dist < closestDistance)
            {
                closestDistance = dist;
                closestAttacker = attacker;
            }
            return;
        }

        AI::CLEAR_PED_TASKS_IMMEDIATELY(attacker, true, false);
        if (attacker != playerPed())
            AI::TASK_COMBAT_PED(attacker, victim.ped, 0, 16);
        broke = true;
    };

    for (Fighter& other : g_runtime.fighters)
    {
        bool sameTeamModeTeam = !freeForAllActive() && other.team == victim.team;
        bool sameBattleRoyaleSquad = freeForAllActive() && victim.group && other.group == victim.group;
        if (sameTeamModeTeam || sameBattleRoyaleSquad || other.ped == victim.ped || !isAlive(other))
            continue;
        breakAttacker(other.ped);
    }

    Ped player = playerPed();
    if (exists(player) &&
        (runtimeRelationToPlayer(victim.team) != PlayerRelation::Friendly ||
         ENTITY::HAS_ENTITY_BEEN_DAMAGED_BY_ENTITY(victim.ped, player, true, true)))
    {
        breakAttacker(player);
    }

    if (!broke && exists(closestAttacker))
    {
        AI::CLEAR_PED_TASKS_IMMEDIATELY(closestAttacker, true, false);
        if (closestAttacker != playerPed())
            AI::TASK_COMBAT_PED(closestAttacker, victim.ped, 0, 16);
        broke = true;
    }

    if (!broke && PED::IS_PED_BEING_STEALTH_KILLED(victim.ped))
        broke = true;

    if (!broke)
        return false;

    if (PED::IS_PED_DEAD_OR_DYING(victim.ped, true) || PED::IS_PED_FATALLY_INJURED(victim.ped))
    {
        PED::RESURRECT_PED(victim.ped);
        PED::REVIVE_INJURED_PED(victim.ped);
    }

    AI::CLEAR_PED_TASKS_IMMEDIATELY(victim.ped, true, false);
    PED::RESET_PED_RAGDOLL_TIMER(victim.ped);
    applyPedTuning(victim);
    int restored = blockedExecutionRecoveryHealthForBoss(victim);
    ENTITY::SET_ENTITY_HEALTH(victim.ped, restored, 0);
    clearVisibleDamage(victim.ped);
    applyExecutionThresholdProtection(victim, restored, false);
    ENTITY::SET_ENTITY_INVINCIBLE(victim.ped, false);
    setFighterCriticalHitsAllowed(victim, false);
    victim.lastHealth = ENTITY::GET_ENTITY_HEALTH(victim.ped);
    victim.lastDamage = t;
    victim.lastTask = 0;
    victim.currentTarget = 0;
    victim.currentTargetStartedAt = 0;
    resetWeaponController(victim);
    victim.lastGrappleBreak = t;
    recordProtectedExecutionFallback(victim, "break-protected-execution-attempt", t);
    return true;
}

Ped findPlayerSquadBodyguardTarget(const Fighter& fighter)
{
    if (!isPlayerBattleRoyaleSquadmate(fighter))
        return 0;

    Ped best{};
    float bestScore = 99999999.0f;
    Vec3 playerPos = entityCoords(playerPed());
    Vec3 self = entityCoords(fighter.ped);

    for (const Fighter& other : g_runtime.fighters)
    {
        if (other.ped == fighter.ped ||
            (fighter.group && other.group == fighter.group) ||
            !isAlive(other))
        {
            continue;
        }

        Vec3 targetPos = entityCoords(other.ped);
        float targetToPlayer = distanceSquared(targetPos, playerPos);
        float targetToSelf = distanceSquared(targetPos, self);
        if (targetToPlayer > 82.0f * 82.0f && targetToSelf > 38.0f * 38.0f)
            continue;

        float score = targetToPlayer * 0.72f + targetToSelf * 0.28f;
        if (score < bestScore)
        {
            bestScore = score;
            best = other.ped;
        }
    }

    return best;
}

bool taskPlayerSquadmateFollow(Fighter& fighter, DWORD t, bool force)
{
    if (!isPlayerBattleRoyaleSquadmate(fighter) || !playerAliveInBattle())
        return false;

    attachFighterToPlayerGroup(fighter);

    float sideOffset{};
    float backOffset{};
    playerSquadFollowOffsets(fighter.playerSquadSlot, sideOffset, backOffset);

    float distToPlayer = distanceSquared(entityCoords(fighter.ped), entityCoords(playerPed()));
    if (distToPlayer > 90.0f * 90.0f)
    {
        moveFighterBesidePlayer(fighter);
        distToPlayer = 0.0f;
    }

    DWORD refreshDelay = distToPlayer > 16.0f * 16.0f ? 850u : 1800u;
    if (!force && t - fighter.lastFollowTask < refreshDelay)
        return true;

    if (distToPlayer > 32.0f * 32.0f)
        AI::CLEAR_PED_TASKS(fighter.ped, true, false);
    AI::CLEAR_PED_SECONDARY_TASK(fighter.ped);
    AI::TASK_FOLLOW_TO_OFFSET_OF_ENTITY(
        fighter.ped,
        playerPed(),
        sideOffset,
        backOffset,
        0.0f,
        2.85f,
        -1,
        1.15f,
        true,
        true,
        false,
        false,
        true);
    fighter.currentTarget = 0;
    fighter.currentTargetStartedAt = 0;
    fighter.lastFollowTask = t;
    fighter.lastTask = t;
    return true;
}

bool taskPlayerBattleRoyaleSquadmate(Fighter& fighter, DWORD t, bool force)
{
    if (!isPlayerBattleRoyaleSquadmate(fighter))
        return false;

    Ped target = findPlayerSquadBodyguardTarget(fighter);
    if (!exists(target))
    {
        if (fighter.scriptedActionType == ScriptedActionType::DynamiteThrow &&
            maintainScriptedCombatAction(fighter, fighter.projectileTarget, t))
            return true;

        resetScriptedActionState(fighter, false);
        return taskPlayerSquadmateFollow(fighter, t, force);
    }

    if (fighter.scriptedActionType != ScriptedActionType::None || fighter.scriptedActionResumeAt != 0)
    {
        Ped actionTarget = isValidEnemyTarget(fighter, fighter.currentTarget) ? fighter.currentTarget : target;
        if (maintainScriptedCombatAction(fighter, actionTarget, t))
            return true;
    }

    Vec3 self = entityCoords(fighter.ped);
    Vec3 playerPos = entityCoords(playerPed());
    Vec3 targetPos = entityCoords(target);
    float distToPlayer = distanceSquared(self, playerPos);
    float targetToSelf = distanceSquared(targetPos, self);
    float targetToPlayer = distanceSquared(targetPos, playerPos);
    if (distToPlayer > 42.0f * 42.0f && targetToSelf > 12.0f * 12.0f)
        return taskPlayerSquadmateFollow(fighter, t, force);

    if (targetToPlayer > 82.0f * 82.0f && targetToSelf > 34.0f * 34.0f)
        return taskPlayerSquadmateFollow(fighter, t, force);

    bool targetChanged = fighter.currentTarget != target;
    if (targetChanged)
    {
        fighter.currentTargetStartedAt = t;
        fighter.pendingCombatWeapon = 0;
        fighter.pendingWeaponTarget = 0;
        fighter.pendingWeaponSince = 0;
        fighter.rangeWeaponCandidate = 0;
        fighter.rangeWeaponCandidateTarget = 0;
        fighter.rangeWeaponCandidateSince = 0;
        resetIdleWatchdogState(fighter, t, target);
    }
    confirmManagedWeaponIfEquipped(fighter, t);
    if (weaponControllerSettling(fighter, t) && !bossUnderSustainedFire(fighter, t))
        return true;

    bool alreadyFightingTarget = PED::IS_PED_IN_COMBAT(fighter.ped, target) != 0;
    bool fleeing = PED::IS_PED_FLEEING(fighter.ped) != 0;
    bool fightingAlly = isFightingTeammate(fighter);
    bool meleeBattle = g_menu.battleType != BattleType::AllWeapons;
    if (!force && !targetChanged && !fightingAlly && alreadyFightingTarget && !fleeing)
    {
        applyAdvancedCombatNudges(fighter, target, t);
        return true;
    }

    DWORD cooldown = meleeBattle ? 1150u : std::max<DWORD>(1050u, combatRetaskDelay(fighter) / 2);
    if (!force && !targetChanged && !fightingAlly && t - fighter.lastTask < cooldown)
    {
        applyAdvancedCombatNudges(fighter, target, t);
        return true;
    }

    if (fleeing || fightingAlly)
        AI::CLEAR_PED_TASKS(fighter.ped, true, false);

    if (fighter.currentTarget != target)
        fighter.currentTargetStartedAt = t;
    fighter.currentTarget = target;
    readyWeapon(fighter, t, force || targetChanged || !alreadyFightingTarget);
    PED::REGISTER_TARGET(fighter.ped, target, true);
    AI::TASK_COMBAT_PED(fighter.ped, target, 0, 16);
    applyAdvancedCombatNudges(fighter, target, t);

    fighter.lastTask = t;
    return true;
}

bool taskNpcBattleRoyaleSquadmate(Fighter& fighter, Ped target, DWORD t, bool force)
{
    if (!isNpcBattleRoyaleSquadmate(fighter))
        return false;

    float teammateDistance{};
    Ped teammate = closestAliveBattleRoyaleSquadmate(fighter, &teammateDistance);
    if (!exists(teammate))
        return false;

    bool meleeBattle = g_menu.battleType != BattleType::AllWeapons;
    float softLimit = meleeBattle ? 5.8f : 15.0f;
    float hardLimit = meleeBattle ? 10.0f : 28.0f;
    bool urgentRegroup = teammateDistance > hardLimit * hardLimit;
    bool looseFormation = teammateDistance > softLimit * softLimit;

    if (!urgentRegroup && !looseFormation)
        return false;

    if (exists(target))
    {
        float targetDistance = distanceSquared(entityCoords(fighter.ped), entityCoords(target));
        float closeFight = meleeBattle ? 5.0f : 14.0f;
        if (!urgentRegroup && targetDistance < closeFight * closeFight)
            return false;
    }

    DWORD refreshDelay = urgentRegroup ? 1200u : 2200u;
    if (!force && t - fighter.lastSquadTask < refreshDelay)
        return true;

    if (urgentRegroup)
        AI::CLEAR_PED_TASKS(fighter.ped, true, false);

    bool canSeeTarget =
        exists(target) &&
        (PED::CAN_PED_IN_COMBAT_SEE_TARGET(fighter.ped, target) ||
         ENTITY::HAS_ENTITY_CLEAR_LOS_TO_ENTITY(fighter.ped, target, 17));
    confirmManagedWeaponIfEquipped(fighter, t);
    if (weaponControllerSettling(fighter, t) && !bossUnderSustainedFire(fighter, t))
        return true;

    if (exists(target) && !meleeBattle && canSeeTarget)
    {
        readyWeapon(fighter, t, true);
        PED::REGISTER_TARGET(fighter.ped, target, true);
        AI::TASK_GO_TO_ENTITY_WHILE_AIMING_AT_ENTITY(
            fighter.ped,
            teammate,
            target,
            combatMoveSpeedForFighter(fighter),
            true,
            4.5f,
            18.0f,
            true,
            false,
            joaat("FIRING_PATTERN_FULL_AUTO"),
            0);
    }
    else
    {
        AI::TASK_GO_TO_ENTITY(
            fighter.ped,
            teammate,
            2400,
            meleeBattle ? 2.2f : 5.5f,
            combatMoveSpeedForFighter(fighter),
            0.0f,
            0);
    }

    fighter.lastSquadTask = t;
    fighter.lastTask = t;
    return true;
}

bool ordinaryIdleWatchdogApplies(const Fighter& fighter)
{
    return g_settings.enableIdleWatchdog &&
        g_menu.battleType == BattleType::AllWeapons &&
        !isEnhancedFighter(fighter);
}

bool soloFfaDeathmatchActive()
{
    return deathmatchActive() && g_runtime.freeForAll && g_runtime.freeForAllTeamSize == 1;
}

DWORD idleWatchdogCheckIntervalForFighter(const Fighter& fighter)
{
    if (ordinaryIdleWatchdogApplies(fighter) && soloFfaDeathmatchActive())
        return g_settings.soloFfaIdleCheckMs;
    return g_settings.ordinaryIdleCheckIntervalMs;
}

DWORD idleWatchdogThresholdForFighter(const Fighter& fighter)
{
    if (ordinaryIdleWatchdogApplies(fighter) && soloFfaDeathmatchActive())
        return g_settings.soloFfaIdleThresholdMs;
    return g_settings.ordinaryIdleThresholdMs;
}

void resetIdleWatchdogState(Fighter& fighter, DWORD t, Ped target = 0)
{
    fighter.lastCombatActivityAt = t;
    fighter.lastIdleRecoveryAt = 0;
    fighter.nextIdleWatchdogCheckAt = t + fighterPhaseOffset(
        fighter,
        std::max<DWORD>(800u, idleWatchdogCheckIntervalForFighter(fighter)),
        137u);
    fighter.lastObservedShotAt = 0;
    fighter.lastObservedMovementAt = t;
    fighter.lastObservedTargetDamageAt = 0;
    fighter.idleWatchdogTarget = target;
    fighter.idleWatchdogPosition = exists(fighter.ped) ? entityCoords(fighter.ped) : Vec3{};
    fighter.idleWatchdogTargetHealth = exists(target) ? ENTITY::GET_ENTITY_HEALTH(target) : 0;
    fighter.consecutiveIdleChecks = 0;
    fighter.idleRecoveryStage = 0;
    fighter.stuckSince = 0;
}

void noteIdleWatchdogActivity(Fighter& fighter, DWORD t, Vec3 pos, Ped target, int targetHealth, bool shot, bool moved, bool damagedTarget)
{
    fighter.lastCombatActivityAt = t;
    if (shot)
        fighter.lastObservedShotAt = t;
    if (moved)
        fighter.lastObservedMovementAt = t;
    if (damagedTarget)
        fighter.lastObservedTargetDamageAt = t;
    fighter.idleWatchdogPosition = pos;
    fighter.idleWatchdogTarget = target;
    fighter.idleWatchdogTargetHealth = targetHealth;
    fighter.consecutiveIdleChecks = 0;
    fighter.idleRecoveryStage = 0;
    fighter.stuckSince = 0;
}

bool ordinaryCombatRecentlyActive(const Fighter& fighter, DWORD t)
{
    if (!ordinaryIdleWatchdogApplies(fighter))
        return true;

    if (PED::IS_PED_SHOOTING(fighter.ped) ||
        PED::IS_PED_RELOADING(fighter.ped) ||
        PED::IS_PED_IN_MELEE_COMBAT(fighter.ped) ||
        PED::GET_MELEE_TARGET_FOR_PED(fighter.ped) ||
        PED::IS_PED_IN_COVER(fighter.ped, false, false) ||
        PED::IS_PED_AIMING_FROM_COVER(fighter.ped) ||
        PED::IS_PED_GOING_INTO_COVER(fighter.ped))
    {
        return true;
    }

    DWORD activeGrace = std::max<DWORD>(idleWatchdogThresholdForFighter(fighter), g_settings.idleSoftRecoveryDelayMs + 600u);
    if (fighter.lastCombatActivityAt != 0 && t - fighter.lastCombatActivityAt < activeGrace)
        return true;
    if (fighter.lastTask != 0 && t - fighter.lastTask < g_settings.idleSoftRecoveryDelayMs)
        return true;
    if (fighter.lastIdleRecoveryAt != 0 && t - fighter.lastIdleRecoveryAt < g_settings.idleSoftRecoveryDelayMs)
        return true;

    return false;
}

bool friendlyBlocksFiringLine(const Fighter& fighter, Ped target)
{
    if (!exists(target))
        return false;

    Vec3 self = entityCoords(fighter.ped);
    Vec3 targetPos = entityCoords(target);
    float toTargetX = targetPos.x - self.x;
    float toTargetY = targetPos.y - self.y;
    float targetDistSq = toTargetX * toTargetX + toTargetY * toTargetY;
    if (targetDistSq < 4.0f * 4.0f)
        return false;

    float targetDist = std::sqrt(targetDistSq);
    float dirX = toTargetX / targetDist;
    float dirY = toTargetY / targetDist;
    float maxAllyDistSq = std::min(targetDistSq, 7.0f * 7.0f);

    for (const Fighter& ally : g_runtime.fighters)
    {
        if (ally.ped == fighter.ped ||
            !isAlive(ally) ||
            isEnemyFighterForBossTactic(fighter, ally))
        {
            continue;
        }

        Vec3 allyPos = entityCoords(ally.ped);
        float allyX = allyPos.x - self.x;
        float allyY = allyPos.y - self.y;
        float allyDistSq = allyX * allyX + allyY * allyY;
        if (allyDistSq < 0.75f * 0.75f || allyDistSq > maxAllyDistSq)
            continue;

        float projection = allyX * dirX + allyY * dirY;
        if (projection < 1.2f || projection > targetDist - 1.0f)
            continue;

        float lateralSq = allyDistSq - projection * projection;
        if (lateralSq <= 2.7f * 2.7f)
            return true;
    }

    return false;
}

Ped findAlternateEnemyTarget(const Fighter& fighter, Ped currentTarget, DWORD t)
{
    Ped best{};
    float bestScore = 99999999.0f;
    Vec3 origin = entityCoords(fighter.ped);
    for (const Fighter& other : g_runtime.fighters)
    {
        bool sameTeamModeTeam = !freeForAllActive() && other.team == fighter.team;
        bool sameBattleRoyaleSquad = freeForAllActive() && fighter.group && other.group == fighter.group;
        if (sameTeamModeTeam ||
            sameBattleRoyaleSquad ||
            other.ped == fighter.ped ||
            other.ped == currentTarget ||
            !isAlive(other))
        {
            continue;
        }

        float dist = distanceSquared(origin, entityCoords(other.ped));
        float score = targetSelectionScore(fighter, other.ped, dist, t);
        if (score < bestScore)
        {
            best = other.ped;
            bestScore = score;
        }
    }

    Ped player = playerPed();
    if (currentTarget != player && fighterRelationToPlayer(fighter) == PlayerRelation::Hostile && exists(player) && !PED::IS_PED_DEAD_OR_DYING(player, true))
    {
        float dist = distanceSquared(origin, entityCoords(player));
        float score = targetSelectionScore(fighter, player, dist, t);
        if (score < bestScore)
            best = player;
    }

    return best;
}

bool issueIdleReposition(Fighter& fighter, Ped target, DWORD t, bool canSeeTarget, bool blockedByFriendly)
{
    if (!exists(target))
        return false;

    Vec3 self = entityCoords(fighter.ped);
    Vec3 targetPos = entityCoords(target);
    float dx = targetPos.x - self.x;
    float dy = targetPos.y - self.y;
    float len = std::sqrt(std::max(0.001f, dx * dx + dy * dy));
    float forwardX = dx / len;
    float forwardY = dy / len;
    float sideSign = ((fighter.spawnIndex + fighter.idleRecoveryStage) % 2 == 0) ? 1.0f : -1.0f;
    float sideX = -forwardY * sideSign;
    float sideY = forwardX * sideSign;
    float minSide = std::max(1.0f, g_settings.idleRepositionMinDistance);
    float maxSide = std::max(minSide, g_settings.idleRepositionMaxDistance);
    int sideCentimeters = randomRange(static_cast<int>(minSide * 100.0f), static_cast<int>(maxSide * 100.0f));
    float sideDistance = static_cast<float>(sideCentimeters) / 100.0f;
    float forwardDistance = canSeeTarget ? (blockedByFriendly ? 1.5f : 0.75f) : 4.0f;
    Vec3 moveTo{
        self.x + sideX * sideDistance + forwardX * forwardDistance,
        self.y + sideY * sideDistance + forwardY * forwardDistance,
        self.z
    };
    snapToGround(moveTo);

    readyWeapon(fighter, t, true);
    PED::REGISTER_TARGET(fighter.ped, target, true);
    if (canSeeTarget)
    {
        AI::TASK_GO_TO_COORD_WHILE_AIMING_AT_ENTITY(
            fighter.ped,
            moveTo.x,
            moveTo.y,
            moveTo.z,
            target,
            combatMoveSpeedForFighter(fighter),
            true,
            1.0f,
            2.4f,
            true,
            0,
            true,
            joaat("FIRING_PATTERN_FULL_AUTO"),
            0,
            0);
    }
    else
    {
        AI::TASK_GO_TO_ENTITY(
            fighter.ped,
            target,
            4200,
            std::max(7.0f, preferredGunRangeForFighter(fighter) * 0.62f),
            combatMoveSpeedForFighter(fighter),
            0.0f,
            0);
    }

    fighter.lastRepositionTask = t;
    fighter.lastTask = t;
    fighter.lastIdleRecoveryAt = t;
    fighter.idleRecoveryStage = std::max(fighter.idleRecoveryStage, 2);
    return true;
}

bool recoverEnhancedFighterIfCombatStalled(Fighter& fighter, Ped target, DWORD t, float dist, bool canSeeTarget)
{
    DWORD checkInterval = fighter.difficulty == Difficulty::Bosses ? 900u : 1200u;

    bool needsProgressBaseline = fighter.lastProgressCheck == 0 || fighter.currentTarget != target;
    if (!needsProgressBaseline && t - fighter.lastProgressCheck < checkInterval)
        return false;

    Vec3 pos = entityCoords(fighter.ped);
    if (needsProgressBaseline)
    {
        fighter.lastProgressPos = pos;
        fighter.lastProgressCheck = t;
        fighter.stuckSince = 0;
        return false;
    }

    float moved = distanceSquared(pos, fighter.lastProgressPos);
    fighter.lastProgressPos = pos;
    fighter.lastProgressCheck = t;

    bool shooting = PED::IS_PED_SHOOTING(fighter.ped) != 0;
    bool reloading = PED::IS_PED_RELOADING(fighter.ped) != 0;
    if (shooting)
        fighter.lastShotTask = t;

    float movementThreshold = 0.32f;
    if (shooting || reloading || moved >= movementThreshold * movementThreshold)
    {
        fighter.stuckSince = 0;
        return false;
    }

    bool actualCanSeeTarget = canSeeTarget;
    if (dist > 12.0f * 12.0f)
    {
        actualCanSeeTarget =
            PED::CAN_PED_IN_COMBAT_SEE_TARGET(fighter.ped, target) ||
            ENTITY::HAS_ENTITY_CLEAR_LOS_TO_ENTITY(fighter.ped, target, 17);
    }

    constexpr float activityRange = 28.0f;
    bool underAttack = t - fighter.lastDamage < 2200u;
    bool stuck =
        dist > activityRange * activityRange ||
        (!actualCanSeeTarget && dist > 12.0f * 12.0f) ||
        underAttack ||
        PED::IS_PED_IN_COMBAT(fighter.ped, target) == 0;

    if (!stuck)
    {
        fighter.stuckSince = 0;
        return false;
    }

    DWORD recoveryDelay = fighter.difficulty == Difficulty::Bosses ? 800u : 1000u;
    if (fighter.stuckSince == 0)
    {
        fighter.stuckSince = underAttack ? t - recoveryDelay : t;
        if (!underAttack)
            return false;
    }

    if (t - fighter.stuckSince < recoveryDelay)
        return false;

    AI::CLEAR_PED_TASKS(fighter.ped, true, false);
    readyWeapon(fighter, t, true);
    PED::REGISTER_TARGET(fighter.ped, target, true);

    float preferredRange = std::min(36.0f, preferredGunRangeForFighter(fighter));
    if (!actualCanSeeTarget || dist > (preferredRange + 8.0f) * (preferredRange + 8.0f))
    {
        float stopRange = std::max(8.0f, preferredRange * 0.68f);
        AI::TASK_GO_TO_ENTITY(fighter.ped, target, 12000, stopRange, combatMoveSpeedForFighter(fighter), 0.0f, 0);
    }
    else
    {
        AI::TASK_COMBAT_PED(fighter.ped, target, 0, 16);
    }

    if (fighter.currentTarget != target)
        fighter.currentTargetStartedAt = t;
    fighter.currentTarget = target;
    fighter.lastTask = t;
    fighter.lastRepositionTask = t;
    fighter.lastProgressPos = pos;
    fighter.lastProgressCheck = t;
    fighter.stuckSince = 0;
    return true;
}

bool recoverFighterIfCombatStalled(Fighter& fighter, Ped target, DWORD t, float dist, bool canSeeTarget)
{
    if (g_runtime.startCountdownActive ||
        g_menu.battleType != BattleType::AllWeapons ||
        !exists(fighter.ped) ||
        !exists(target) ||
        protectedScriptedActionActive(fighter))
    {
        fighter.stuckSince = 0;
        return false;
    }

    if (isEnhancedFighter(fighter))
        return recoverEnhancedFighterIfCombatStalled(fighter, target, t, dist, canSeeTarget);

    if (!ordinaryIdleWatchdogApplies(fighter))
        return false;

    bool targetChanged = fighter.idleWatchdogTarget != target || fighter.currentTarget != target;
    if (targetChanged || fighter.nextIdleWatchdogCheckAt == 0 || fighter.lastCombatActivityAt == 0)
    {
        resetIdleWatchdogState(fighter, t, target);
        return false;
    }

    if (t < fighter.nextIdleWatchdogCheckAt)
        return false;
    DWORD checkInterval = idleWatchdogCheckIntervalForFighter(fighter) + static_cast<DWORD>(fighter.spawnIndex % 5) * 140u;
    fighter.nextIdleWatchdogCheckAt = t + std::max<DWORD>(800u, checkInterval);

    Vec3 pos = entityCoords(fighter.ped);
    float moved = distanceSquared(pos, fighter.idleWatchdogPosition);
    int targetHealth = exists(target) ? ENTITY::GET_ENTITY_HEALTH(target) : 0;
    bool targetDamaged = fighter.idleWatchdogTargetHealth > 0 && targetHealth > 0 && targetHealth < fighter.idleWatchdogTargetHealth;

    bool shooting = PED::IS_PED_SHOOTING(fighter.ped) != 0;
    bool reloading = PED::IS_PED_RELOADING(fighter.ped) != 0;
    if (shooting)
        fighter.lastShotTask = t;

    float movementThreshold = 0.32f;
    bool movedMeaningfully = moved >= movementThreshold * movementThreshold;
    bool meleeActive =
        PED::IS_PED_IN_MELEE_COMBAT(fighter.ped) ||
        PED::GET_MELEE_TARGET_FOR_PED(fighter.ped);
    bool coverActive =
        PED::IS_PED_IN_COVER(fighter.ped, false, false) ||
        PED::IS_PED_AIMING_FROM_COVER(fighter.ped) ||
        PED::IS_PED_GOING_INTO_COVER(fighter.ped);
    bool recentlyDamaged = t - fighter.lastDamage < 1800u;
    if (shooting || reloading || movedMeaningfully || meleeActive || coverActive || targetDamaged || recentlyDamaged)
    {
        noteIdleWatchdogActivity(fighter, t, pos, target, targetHealth, shooting, movedMeaningfully, targetDamaged);
        return false;
    }

    fighter.idleWatchdogPosition = pos;
    fighter.idleWatchdogTargetHealth = targetHealth;
    if (fighter.lastCombatActivityAt == 0)
        fighter.lastCombatActivityAt = t;

    if (t - fighter.lastCombatActivityAt < idleWatchdogThresholdForFighter(fighter))
        return false;

    ++fighter.consecutiveIdleChecks;
    if (fighter.consecutiveIdleChecks < g_settings.ordinaryIdleConsecutiveChecks)
        return false;

    bool actualCanSeeTarget =
        PED::CAN_PED_IN_COMBAT_SEE_TARGET(fighter.ped, target) ||
        ENTITY::HAS_ENTITY_CLEAR_LOS_TO_ENTITY(fighter.ped, target, 17);
    bool blockedByFriendly = !soloFfaDeathmatchActive() && friendlyBlocksFiringLine(fighter, target);

    if (fighter.idleRecoveryStage <= 0)
    {
        readyWeapon(fighter, t, true);
        PED::REGISTER_TARGET(fighter.ped, target, true);
        AI::TASK_COMBAT_PED(fighter.ped, target, 0, 16);
        fighter.lastTask = t;
        fighter.lastIdleRecoveryAt = t;
        fighter.idleRecoveryStage = 1;
        return true;
    }

    if (fighter.lastIdleRecoveryAt != 0 && t - fighter.lastIdleRecoveryAt < g_settings.idleSoftRecoveryDelayMs)
        return false;

    if (fighter.idleRecoveryStage == 1)
        return issueIdleReposition(fighter, target, t, actualCanSeeTarget, blockedByFriendly);

    if (fighter.lastIdleRecoveryAt != 0 && t - fighter.lastIdleRecoveryAt < g_settings.idleHardRecoveryCooldownMs)
        return false;

    Ped recoveryTarget = target;
    if (g_settings.idleAllowForcedTargetChange && fighter.consecutiveIdleChecks > g_settings.ordinaryIdleConsecutiveChecks)
    {
        Ped alternate = findAlternateEnemyTarget(fighter, target, t);
        if (exists(alternate))
            recoveryTarget = alternate;
    }

    AI::CLEAR_PED_TASKS(fighter.ped, true, false);
    readyWeapon(fighter, t, true);
    PED::REGISTER_TARGET(fighter.ped, recoveryTarget, true);
    if (recoveryTarget != target)
    {
        fighter.currentTargetStartedAt = t;
        fighter.currentTarget = recoveryTarget;
    }
    AI::TASK_COMBAT_PED(fighter.ped, recoveryTarget, 0, 16);

    fighter.lastTask = t;
    fighter.lastRepositionTask = t;
    fighter.lastIdleRecoveryAt = t;
    fighter.lastProgressPos = pos;
    fighter.lastProgressCheck = t;
    fighter.idleRecoveryStage = 3;
    return true;
}

void taskFighter(Fighter& fighter, DWORD t, bool force)
{
    if (!isAlive(fighter))
        return;

    if (PED::IS_PED_RAGDOLL(fighter.ped) || PED::IS_PED_RUNNING_RAGDOLL_TASK(fighter.ped))
    {
        enforceBossRagdollProtection(fighter, false);
        if (fighter.difficulty != Difficulty::Bosses ||
            PED::IS_PED_RAGDOLL(fighter.ped) ||
            PED::IS_PED_RUNNING_RAGDOLL_TASK(fighter.ped))
        {
            fighter.lastTask = 0;
            return;
        }
    }

    if (taskPlayerBattleRoyaleSquadmate(fighter, t, force))
        return;

    if (fighter.scriptedActionType == ScriptedActionType::DynamiteThrow ||
        fighter.scriptedActionType == ScriptedActionType::BossEvasion)
    {
        if (maintainScriptedCombatAction(fighter, fighter.currentTarget, t))
            return;
    }
    else if (fighter.scriptedActionType != ScriptedActionType::None)
    {
        bool directlyAiming = false;
        bool recentlyDamagedByPlayer = false;
        bool playerThreat =
            playerIsActivelyThreateningBoss(fighter, t, directlyAiming, recentlyDamagedByPlayer) &&
            ((directlyAiming && t >= fighter.nextPlayerThreatDodgeAt) ||
             (recentlyDamagedByPlayer &&
              (fighter.lastPlayerThreatDodgeAt == 0 ||
               t - fighter.lastPlayerThreatDodgeAt >= kPlayerDamageDodgeMinimumGapMs)));
        if (playerThreat)
            resetScriptedActionState(fighter, false);
        else if (maintainScriptedCombatAction(fighter, fighter.currentTarget, t))
            return;
    }
    else if (fighter.scriptedActionResumeAt != 0 && isValidEnemyTarget(fighter, fighter.currentTarget))
    {
        if (maintainScriptedCombatAction(fighter, fighter.currentTarget, t))
            return;
    }
    else if (fighter.scriptedActionResumeAt != 0)
    {
        resetScriptedActionState(fighter, false);
    }

    Ped previousTarget = fighter.currentTarget;
    Ped target = selectCombatTarget(fighter, t, force);
    bool targetChanged = previousTarget != target;
    if (targetChanged)
    {
        fighter.currentTargetStartedAt = t;
        fighter.pendingCombatWeapon = 0;
        fighter.pendingWeaponTarget = 0;
        fighter.pendingWeaponSince = 0;
        fighter.rangeWeaponCandidate = 0;
        fighter.rangeWeaponCandidateTarget = 0;
        fighter.rangeWeaponCandidateSince = 0;
    }
    if (taskNpcBattleRoyaleSquadmate(fighter, target, t, force))
    {
        if (exists(target))
        {
            if (fighter.currentTarget != target)
                fighter.currentTargetStartedAt = t;
            fighter.currentTarget = target;
        }
        return;
    }

    confirmManagedWeaponIfEquipped(fighter, t);
    if (weaponControllerSettling(fighter, t) && !bossUnderSustainedFire(fighter, t))
        return;

    if (!exists(target))
        return;

    float dist = distanceSquared(entityCoords(fighter.ped), entityCoords(target));
    bool enhancedFighter = isEnhancedFighter(fighter);
    bool canSeeTarget = true;
    if (enhancedFighter)
    {
        canSeeTarget =
            PED::CAN_PED_IN_COMBAT_SEE_TARGET(fighter.ped, target) ||
            ENTITY::HAS_ENTITY_CLEAR_LOS_TO_ENTITY(fighter.ped, target, 17);
    }
    if (recoverFighterIfCombatStalled(fighter, target, t, dist, canSeeTarget))
        return;

    bool alreadyFightingTarget = PED::IS_PED_IN_COMBAT(fighter.ped, target) != 0;
    bool fleeing = PED::IS_PED_FLEEING(fighter.ped) != 0;
    bool ordinaryCombatHealthy = enhancedFighter || ordinaryCombatRecentlyActive(fighter, t);
    if (!enhancedFighter && !force && !targetChanged && alreadyFightingTarget && !fleeing && ordinaryCombatHealthy)
    {
        if (taskOrdinaryAdvanceIfDistant(fighter, target, t, dist, false, canSeeTarget))
            return;
        if (taskOrdinaryCombatMovementNudge(fighter, target, t, dist, canSeeTarget))
            return;
        return;
    }

    bool fightingAlly = (enhancedFighter || !alreadyFightingTarget) ? isFightingTeammate(fighter) : false;
    bool meleeBattle = g_menu.battleType != BattleType::AllWeapons;
    if (enhancedFighter && taskPursueDistantTarget(fighter, target, t, dist, force || targetChanged || fightingAlly))
        return;

    DWORD cooldown = meleeBattle ? 1400u : combatRetaskDelay(fighter);
    if (!force && !targetChanged && !fightingAlly && t - fighter.lastTask < cooldown)
    {
        applyAdvancedCombatNudges(fighter, target, t);
        return;
    }

    if (fleeing || fightingAlly)
        AI::CLEAR_PED_TASKS(fighter.ped, true, false);

    if (fighter.currentTarget != target)
        fighter.currentTargetStartedAt = t;
    fighter.currentTarget = target;
    readyWeapon(fighter, t, force || targetChanged || !alreadyFightingTarget);
    PED::REGISTER_TARGET(fighter.ped, target, true);

    if (!enhancedFighter)
    {
        if (taskOrdinaryAdvanceIfDistant(fighter, target, t, dist, force || targetChanged || !alreadyFightingTarget, canSeeTarget))
            return;
        if (taskOrdinaryCombatMovementNudge(fighter, target, t, dist, canSeeTarget))
            return;

        AI::TASK_COMBAT_PED(fighter.ped, target, 0, 16);
        fighter.lastTask = t;
        return;
    }

    if (meleeBattle)
    {
        if (tryBossGrapple(fighter, target, t, dist))
            return;

        if (dist > 4.0f * 4.0f)
            AI::TASK_GO_TO_ENTITY(fighter.ped, target, 2200, 1.1f, 4.5f, 0.0f, 0);
        AI::TASK_PUT_PED_DIRECTLY_INTO_MELEE(fighter.ped, target, 0.0f, -1.0f, 0.0f, 0.0f, 0);
    }
    else
    {
        float preferredRange = preferredGunRangeForFighter(fighter);
        bool usingTacticalCover = isAdvancedFighter(fighter) &&
            (PED::IS_PED_IN_COVER(fighter.ped, false, false) ||
             PED::IS_PED_AIMING_FROM_COVER(fighter.ped) ||
             PED::IS_PED_GOING_INTO_COVER(fighter.ped));
        if (usingTacticalCover)
        {
            applyAdvancedCombatNudges(fighter, target, t);
            fighter.lastTask = t;
            return;
        }

        if (dist > preferredRange * preferredRange &&
            taskApproachTarget(fighter, target, t, force || targetChanged || !alreadyFightingTarget, canSeeTarget))
        {
            applyAdvancedCombatNudges(fighter, target, t);
            return;
        }

        AI::TASK_COMBAT_PED(fighter.ped, target, 0, 16);
        applyAdvancedCombatNudges(fighter, target, t);
    }

    fighter.lastTask = t;
}

void reviveFromCriticalHit(Fighter& fighter)
{
    if (!exists(fighter.ped))
        return;

    if (fighter.difficulty != Difficulty::Bosses &&
        fighter.difficulty != Difficulty::Extreme &&
        fighter.difficulty != Difficulty::Special &&
        fighter.criticalRevives >= 2)
    {
        return;
    }

    int threshold = executionHealthThreshold(fighter);
    if (threshold > 0 && fighter.lastHealth > 0 && fighter.lastHealth <= threshold)
    {
        return;
    }

    PED::RESURRECT_PED(fighter.ped);
    PED::REVIVE_INJURED_PED(fighter.ped);
    AI::CLEAR_PED_TASKS_IMMEDIATELY(fighter.ped, true, false);
    int health = (fighter.difficulty == Difficulty::Bosses ||
        fighter.difficulty == Difficulty::Extreme ||
        fighter.difficulty == Difficulty::Special) ?
        blockedExecutionRecoveryHealthForBoss(fighter) :
        (fighter.heals ? std::max(260, fighter.maxHealth / 2) : std::max(130, fighter.maxHealth / 3));
    ENTITY::SET_ENTITY_HEALTH(fighter.ped, health, 0);
    clearVisibleDamage(fighter.ped);
    applyExecutionThresholdProtection(fighter, health, false);
    ENTITY::SET_ENTITY_INVINCIBLE(fighter.ped, false);
    recordProtectedExecutionFallback(fighter, "critical-revive-fallback", now());
    ++fighter.criticalRevives;
    fighter.lastHealth = health;
    fighter.lastDamage = now();
    fighter.lastTask = 0;
    fighter.lastProgressCheck = 0;
    fighter.stuckSince = 0;
    fighter.currentTarget = 0;
    fighter.currentTargetStartedAt = 0;
    resetIdleWatchdogState(fighter, now(), 0);
    resetScriptedActionState(fighter, true);
    resetWeaponController(fighter);
}

void resetFighterForReplacementPed(Fighter& fighter, DWORD t)
{
    fighter.deathRecorded = false;
    fighter.pendingRespawn = false;
    fighter.respawnState = DeathmatchRespawnState::Complete;
    fighter.respawnAt = 0;
    fighter.respawnReadyAt = 0;
    fighter.corpseDeleteAt = 0;
    fighter.respawnAttempts = 0;
    fighter.finishPosition = 0;
    resetFighterCorpseState(fighter);
    fighter.criticalRevives = 0;
    fighter.cinematicRecoveryActive = false;
    fighter.cinematicRecoveryStarted = 0;
    fighter.cinematicRecoveryRecoverAt = 0;
    fighter.cinematicRecoveryHealth = 0;
    fighter.spawnedAt = t;
    fighter.lastDamage = t;
    fighter.lastHeal = t;
    fighter.lastTask = 0;
    resetWeaponController(fighter);
    fighter.lastWeaponSwitch = t;
    fighter.lastProgressCheck = 0;
    fighter.stuckSince = 0;
    resetIdleWatchdogState(fighter, t, 0);
    resetScriptedActionState(fighter, true);
    fighter.lastShotTask = 0;
    fighter.lastActualShot = 0;
    fighter.lastRepositionTask = 0;
    fighter.lastEvasiveTask = 0;
    fighter.lastDynamiteTask = 0;
    fighter.lastDefensiveTask = 0;
    fighter.lastSpecialTask = 0;
    fighter.crouchUntil = 0;
    fighter.defensiveCombatStartedAt = 0;
    fighter.defensiveCombatUntil = 0;
    fighter.recentDamageWindowStarted = 0;
    fighter.recentDamageHits = 0;
    fighter.bossBurstsSinceMovement = 0;
    fighter.wasInCover = false;
    fighter.currentTarget = 0;
    fighter.currentTargetStartedAt = 0;
    fighter.pendingCombatWeapon = 0;
    fighter.pendingWeaponTarget = 0;
    fighter.pendingWeaponSince = 0;
    fighter.rangeWeaponCandidate = 0;
    fighter.rangeWeaponCandidateTarget = 0;
    fighter.rangeWeaponCandidateSince = 0;
    fighter.lastBlipUpdate = 0;
    fighter.lastBlipRelation = -1;
    seedFighterUpdateSchedule(fighter, t);
}

bool respawnDeathmatchFighter(Fighter& fighter, DWORD t)
{
    if (!deathmatchActive() ||
        !fighter.pendingRespawn ||
        fighter.respawnState != DeathmatchRespawnState::Queued ||
        t < fighter.respawnReadyAt ||
        exists(fighter.ped))
    {
        return false;
    }

    if (deathmatchRespawnPressureHigh())
        return false;

    Hash model = fighter.model;
    if (!requestModel(model))
        return false;
    STREAMING::REQUEST_COLLISION_FOR_MODEL(model);

    fighter.respawnState = DeathmatchRespawnState::Spawning;
    Vec3 pos{};
    bool resolvedSpawn = false;
    bool originalTeamDeathmatchRespawn =
        g_settings.respawnTeamDeathmatchAtOriginalSpawn &&
        !g_runtime.freeForAll &&
        fighter.originalSpawnSet;
    int respawnIndex = fighter.spawnIndex + randomRange(0, 4);
    if (originalTeamDeathmatchRespawn)
    {
        pos = fighter.originalSpawn;
        resolvedSpawn = true;
    }
    else
    {
        for (int attempt = 0; attempt < kSpawnCreateAttempts; ++attempt)
        {
            if (resolveSpawnSlotPosition(fighter.team, respawnIndex, attempt, pos))
            {
                resolvedSpawn = true;
                break;
            }

            if (battleSpawnDistance() >= kSpawnInwardFallbackDistance && attempt > 0 && attempt % 8 == 0)
                WAIT(0);
        }
    }
    if (!resolvedSpawn)
        pos = spawnSlot(fighter.team, respawnIndex);

    float heading = originalTeamDeathmatchRespawn ? fighter.originalHeading : headingToward(pos, g_runtime.battleCenter);
    bool playerSquadRespawn =
        g_runtime.freeForAll &&
        g_runtime.playerFreeForAllGroup &&
        fighter.group == g_runtime.playerFreeForAllGroup &&
        !g_runtime.playerEliminated;
    if (playerSquadRespawn)
    {
        pos = playerOffsetPosition(2.0f + static_cast<float>(fighter.playerSquadSlot) * 1.1f, -3.2f);
        heading = ENTITY::GET_ENTITY_HEADING(playerPed());
    }

    STREAMING::REQUEST_COLLISION_AT_COORD(pos.x, pos.y, pos.z);
    PATHFIND::ADD_NAVMESH_REQUIRED_REGION(pos.x, pos.y, 10.0f);
    Ped newPed = PED::CREATE_PED(model, pos.x, pos.y, pos.z, heading, true, true, true, true);
    if (!exists(newPed) && !playerSquadRespawn)
    {
        for (int attempt = 1; attempt < kSpawnCreateAttempts; ++attempt)
        {
            if (!resolveSpawnSlotPosition(fighter.team, respawnIndex, attempt, pos))
                continue;

            heading = headingToward(pos, g_runtime.battleCenter);
            STREAMING::REQUEST_COLLISION_AT_COORD(pos.x, pos.y, pos.z);
            PATHFIND::ADD_NAVMESH_REQUIRED_REGION(pos.x, pos.y, 10.0f);
            if (battleSpawnDistance() >= kSpawnInwardFallbackDistance && attempt % 6 == 0)
                WAIT(0);

            newPed = PED::CREATE_PED(model, pos.x, pos.y, pos.z, heading, true, true, true, true);
            if (exists(newPed))
                break;
        }
    }
    STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);
    if (!exists(newPed))
    {
        fighter.respawnState = DeathmatchRespawnState::Failed;
        ++g_runtime.deathmatchRespawnAllocationFailures;
        return false;
    }

    fighter.ped = newPed;
    fighter.model = model;
    fighter.respawnState = DeathmatchRespawnState::Finalising;
    ENTITY::SET_ENTITY_AS_MISSION_ENTITY(fighter.ped, true, true);
    PED::SET_PED_RELATIONSHIP_GROUP_DEFAULT_HASH(fighter.ped, fighter.group);
    PED::SET_PED_RELATIONSHIP_GROUP_HASH(fighter.ped, fighter.group);
    if (fighter.voiceName && *fighter.voiceName)
        AUDIO::SET_AMBIENT_VOICE_NAME(fighter.ped, const_cast<char*>(fighter.voiceName));

    ENTITY::SET_ENTITY_COORDS_NO_OFFSET(fighter.ped, pos.x, pos.y, pos.z, false, false, false);
    ENTITY::SET_ENTITY_HEADING(fighter.ped, heading);
    AI::CLEAR_PED_TASKS_IMMEDIATELY(fighter.ped, true, false);
    PED::RESET_PED_RAGDOLL_TIMER(fighter.ped);
    makePedVisible(fighter.ped);
    applyPedOutfit(fighter.ped, fighter.outfitIndex);
    ENTITY::SET_ENTITY_INVINCIBLE(fighter.ped, false);
    ENTITY::SET_ENTITY_HEALTH(fighter.ped, fighter.maxHealth, 0);
    clearVisibleDamage(fighter.ped);

    resetFighterForReplacementPed(fighter, t);
    fighter.lastHealth = ENTITY::GET_ENTITY_HEALTH(fighter.ped);

    applyPedTuning(fighter);
    applyProtectedHeadshotMultiplierTest(fighter, "deathmatch-respawn");
    applyExecutionThresholdProtection(fighter, ENTITY::GET_ENTITY_HEALTH(fighter.ped), false);
    restoreFighterWeapons(fighter, t, true);
    applyDamagePermissions(fighter);
    removeFighterBlip(fighter);
    ensureFighterBlip(fighter);
    taskFighter(fighter, t, true);
    ++g_runtime.deathmatchRespawnsCreated;
    return true;
}

void enqueueDeathmatchRespawn(int fighterIndex)
{
    if (fighterIndex < 0 || fighterIndex >= static_cast<int>(g_runtime.fighters.size()))
        return;

    Fighter& fighter = g_runtime.fighters[static_cast<size_t>(fighterIndex)];
    if (!fighter.pendingRespawn || fighter.respawnState == DeathmatchRespawnState::Queued)
        return;

    fighter.respawnState = DeathmatchRespawnState::Queued;
    g_runtime.deathmatchRespawnQueue.push_back(fighterIndex);
}

void updateDeathmatchRespawnSystem(DWORD t)
{
    if (!deathmatchActive())
        return;

    for (int i = 0; i < static_cast<int>(g_runtime.fighters.size()); ++i)
    {
        Fighter& fighter = g_runtime.fighters[static_cast<size_t>(i)];

        if (fighter.respawnState == DeathmatchRespawnState::WaitingForCorpseDeletion)
        {
            bool onScreen = exists(fighter.ped) && ENTITY::IS_ENTITY_ON_SCREEN(fighter.ped);
            bool pressureCleanup =
                (exists(fighter.ped) && !onScreen) ||
                deathmatchRespawnPressureHigh();
            if (pressureCleanup || t >= fighter.corpseDeleteAt)
            {
                if (deleteDeathmatchPedEntity(fighter))
                {
                    fighter.pendingRespawn = true;
                    fighter.respawnState = DeathmatchRespawnState::WaitingForRespawn;
                }
                else
                {
                    fighter.corpseDeleteAt = t + 150u;
                }
            }
        }

        if (fighter.pendingRespawn &&
            fighter.respawnState == DeathmatchRespawnState::WaitingForRespawn &&
            t >= fighter.respawnReadyAt)
        {
            enqueueDeathmatchRespawn(i);
        }
    }

    int processed = 0;
    while (processed < g_settings.deathmatchMaximumRespawnsPerFrame &&
        g_runtime.deathmatchRespawnQueueCursor < g_runtime.deathmatchRespawnQueue.size() &&
        t >= g_runtime.nextDeathmatchRespawnAllowedAt)
    {
        int fighterIndex = g_runtime.deathmatchRespawnQueue[g_runtime.deathmatchRespawnQueueCursor++];
        if (fighterIndex < 0 || fighterIndex >= static_cast<int>(g_runtime.fighters.size()))
            continue;

        Fighter& fighter = g_runtime.fighters[static_cast<size_t>(fighterIndex)];
        if (!fighter.pendingRespawn || fighter.respawnState != DeathmatchRespawnState::Queued)
            continue;
        if (t < fighter.respawnReadyAt)
        {
            fighter.respawnState = DeathmatchRespawnState::WaitingForRespawn;
            continue;
        }

        if (respawnDeathmatchFighter(fighter, t))
        {
            ++processed;
            ++g_runtime.deathmatchRespawnsThisFrame;
            g_runtime.deathmatchMaxRespawnsInFrame =
                std::max(g_runtime.deathmatchMaxRespawnsInFrame, g_runtime.deathmatchRespawnsThisFrame);
            g_runtime.nextDeathmatchRespawnAllowedAt = t + g_settings.deathmatchMinimumRespawnGapMs;
        }
        else
        {
            ++fighter.respawnAttempts;
            fighter.pendingRespawn = true;
            fighter.respawnState = DeathmatchRespawnState::WaitingForRespawn;
            fighter.respawnReadyAt = t + std::min<DWORD>(2500u, 450u + static_cast<DWORD>(fighter.respawnAttempts) * 250u);
            fighter.respawnAt = fighter.respawnReadyAt;
        }
    }

    if (g_runtime.deathmatchRespawnQueueCursor >= g_runtime.deathmatchRespawnQueue.size())
    {
        g_runtime.deathmatchRespawnQueue.clear();
        g_runtime.deathmatchRespawnQueueCursor = 0;
    }
    else if (g_runtime.deathmatchRespawnQueueCursor > 32)
    {
        g_runtime.deathmatchRespawnQueue.erase(
            g_runtime.deathmatchRespawnQueue.begin(),
            g_runtime.deathmatchRespawnQueue.begin() + static_cast<std::ptrdiff_t>(g_runtime.deathmatchRespawnQueueCursor));
        g_runtime.deathmatchRespawnQueueCursor = 0;
    }
}

#if BATTLECREATOR_ENABLE_DEATHMATCH_DIAGNOSTICS
int livingActiveBattlePedCount()
{
    int count = 0;
    for (const Fighter& fighter : g_runtime.fighters)
    {
        if (isAlive(fighter))
            ++count;
    }
    return count;
}

int existingDeadBattlePedCount()
{
    int count = 0;
    for (const Fighter& fighter : g_runtime.fighters)
    {
        if (exists(fighter.ped) &&
            (PED::IS_PED_DEAD_OR_DYING(fighter.ped, true) || PED::IS_PED_FATALLY_INJURED(fighter.ped)))
        {
            ++count;
        }
    }
    return count;
}

int activeRespawnPhaseCount()
{
    int count = 0;
    for (const Fighter& fighter : g_runtime.fighters)
    {
        if (fighter.respawnState == DeathmatchRespawnState::Spawning ||
            fighter.respawnState == DeathmatchRespawnState::Finalising)
        {
            ++count;
        }
    }
    return count;
}

void emitDeathmatchDiagnostics(DWORD t)
{
    if (!deathmatchActive())
        return;
    if (g_runtime.nextDeathmatchDiagnosticsAt != 0 && t < g_runtime.nextDeathmatchDiagnosticsAt)
        return;

    g_runtime.nextDeathmatchDiagnosticsAt = t + 5000u;
    char buffer[768]{};
    std::snprintf(
        buffer,
        sizeof(buffer),
        "[BattleCreator][DeathmatchPerf] living=%d deadExisting=%d pendingCorpses=%d normalCorpses=%d "
        "trackedWeapons=%d weaponsDeleted=%d pendingRespawns=%d queuedRespawns=%d activeRespawnPhase=%d "
        "respawnsCreated=%d respawnFailures=%d maxRespawnsFrame=%d retargetRequested=%d retargetProcessed=%d "
        "retargetDeferred=%d snapshotRefreshes=%d snapshotScans=%d liveScans=%d staleRefsCleared=%d totalExistingPeds=%d\n",
        livingActiveBattlePedCount(),
        existingDeadBattlePedCount(),
        pendingDeathmatchCorpseDeletionCount(),
        static_cast<int>(g_runtime.battleCorpses.size()),
        trackedDroppedWeaponObjectCount(),
        g_runtime.trackedDroppedWeaponsDeleted,
        pendingDeathmatchRespawnCount(),
        queuedDeathmatchRespawnCount(),
        activeRespawnPhaseCount(),
        g_runtime.deathmatchRespawnsCreated,
        g_runtime.deathmatchRespawnAllocationFailures,
        g_runtime.deathmatchMaxRespawnsInFrame,
        g_runtime.deathmatchRetargetsRequested,
        g_runtime.deathmatchRetargetsProcessed,
        g_runtime.deathmatchRetargetsDeferred,
        g_runtime.fighterSnapshotRefreshes,
        g_runtime.targetScansUsingSnapshots,
        g_runtime.targetScansWithoutSnapshots,
        g_runtime.staleTargetReferencesCleared,
        livingActiveBattlePedCount() + existingDeadBattlePedCount());
    OutputDebugStringA(buffer);
}
#endif

void maintainFighter(Fighter& fighter)
{
    if (!exists(fighter.ped))
    {
        removeFighterBlip(fighter);
        return;
    }

    DWORD t = now();
    bool dead = PED::IS_PED_DEAD_OR_DYING(fighter.ped, true) || PED::IS_PED_FATALLY_INJURED(fighter.ped);
    int health = ENTITY::GET_ENTITY_HEALTH(fighter.ped);
    bool boss = fighter.difficulty == Difficulty::Bosses;
    if (dead && fighter.deathRecorded)
    {
        removeFighterBlip(fighter);
        return;
    }

    if (!dead)
    {
        if (shouldPollManagedWeapon(fighter, t))
            confirmManagedWeaponIfEquipped(fighter, t);
        hasTemporaryWeaponOverride(fighter, t);
    }
    if (PED::IS_PED_SHOOTING(fighter.ped))
    {
        fighter.lastActualShot = t;
        fighter.lastShotTask = t;
        fighter.lastCombatActivityAt = t;
        fighter.lastObservedShotAt = t;
    }
    bool currentlyInCover = boss &&
        (PED::IS_PED_IN_COVER(fighter.ped, false, false) ||
         PED::IS_PED_AIMING_FROM_COVER(fighter.ped));
    if (currentlyInCover && !fighter.wasInCover)
    {
        fighter.recentDamageHits = 0;
        fighter.recentDamageWindowStarted = 0;
    }
    fighter.wasInCover = currentlyInCover;
    enforceBossRagdollProtection(fighter, dead);
    if (fighter.crouchUntil != 0 && t > fighter.crouchUntil)
    {
        setPedCrouchMovement(fighter.ped, false);
        fighter.crouchUntil = 0;
    }

    applyExecutionThresholdProtection(fighter, health, dead);
    if (restorePlayerFriendlyFire(fighter, health, dead, t))
        return;
    redirectFriendlyAwayFromPlayer(fighter, t);

    if (!dead && health > fighter.maxHealth)
    {
        ENTITY::SET_ENTITY_HEALTH(fighter.ped, fighter.maxHealth, 0);
        health = fighter.maxHealth;
    }

    if (shouldProtectCinematicKills(fighter) && (dead || health < fighter.lastHealth))
    {
        debugProtectedHeadshotMultiplierTest(
            fighter,
            "damage-observed",
            fighter.lastHealth,
            health,
            fighter.cinematicRecoveryActive);
    }

    if (maintainCinematicExecutionRecovery(fighter, t, health, dead))
    {
        debugProtectedHeadshotMultiplierTest(
            fighter,
            "cinematic-recovery-maintained",
            fighter.lastHealth,
            health,
            true);
        return;
    }

    bool stealthKillAttempt = fighter.hardened && PED::IS_PED_BEING_STEALTH_KILLED(fighter.ped);
    bool criticalAttempt = fighter.hardened &&
        (stealthKillAttempt ||
         PED::IS_PED_RAGDOLL(fighter.ped) ||
         PED::IS_PED_RUNNING_RAGDOLL_TASK(fighter.ped));
    bool likelyInstantKill = dead && (boss ? fighter.lastHealth > 0 : fighter.lastHealth > fighter.maxHealth / 3);
    bool underExecutionThreshold = underExecutionHealthThreshold(fighter, health, dead);
    bool protectCinematicKill = shouldProtectCinematicKills(fighter);
    bool blockCinematicFallback = protectCinematicKill && !underExecutionThreshold;
    bool allowHardenedExecution = fighter.hardened && underExecutionThreshold && (stealthKillAttempt || likelyInstantKill);

    if (!allowHardenedExecution && blockCinematicFallback && stealthKillAttempt && breakProtectedExecutionAttempt(fighter, t, true))
        return;

    if (!allowHardenedExecution && blockCinematicFallback && fighter.hardened && likelyInstantKill && !stealthKillAttempt)
    {
        debugProtectedHeadshotMultiplierTest(fighter, "critical-revive-fallback", fighter.lastHealth, health, false);
        reviveFromCriticalHit(fighter);
        return;
    }

    if (!allowHardenedExecution &&
        blockCinematicFallback &&
        fighter.hardened &&
        stealthKillAttempt &&
        beginCinematicExecutionRecovery(fighter, t, health, dead))
    {
        return;
    }

    if (!allowHardenedExecution && blockCinematicFallback && fighter.hardened && (criticalAttempt || likelyInstantKill))
    {
        debugProtectedHeadshotMultiplierTest(fighter, "critical-revive-fallback", fighter.lastHealth, health, false);
        reviveFromCriticalHit(fighter);
        return;
    }

    if (dead)
    {
        resetScriptedActionState(fighter, true);
        recordFighterDeath(fighter);
        removeFighterBlip(fighter);
        return;
    }

    if (g_menu.battleType != BattleType::NoWeapons &&
        !isUnarmedWeapon(fighter.combatWeapon) &&
        !WEAPON::HAS_PED_GOT_WEAPON(fighter.ped, fighter.combatWeapon, false, false) &&
        t - fighter.lastWeaponReady > 900u)
    {
        restoreFighterWeapons(fighter, t, true);
    }

    bool damagedByPlayer = ENTITY::HAS_ENTITY_BEEN_DAMAGED_BY_ENTITY(fighter.ped, playerPed(), true, true);
    if (damagedByPlayer)
        provokeNeutralTeamByPlayer(fighter, t);

    if (health < fighter.lastHealth)
    {
        if (damagedByPlayer)
            fighter.lastPlayerDamage = t;
        applyHitDamageBonuses(fighter, t, health);
        fighter.lastDamage = t;
        fighter.lastCombatActivityAt = t;
        if (boss)
        {
            if (fighter.recentDamageWindowStarted == 0 || t - fighter.recentDamageWindowStarted > 4500u)
            {
                fighter.recentDamageWindowStarted = t;
                fighter.recentDamageHits = 0;
            }
            fighter.recentDamageHits = std::min(8, fighter.recentDamageHits + 1);
            if (fighter.recentDamageHits == 2)
            {
                fighter.defensiveCombatStartedAt = t;
                fighter.defensiveCombatUntil = t + 9000u;
                if (!protectedScriptedActionActive(fighter))
                    resetScriptedActionState(fighter, false);
                PED::SET_PED_COMBAT_MOVEMENT(fighter.ped, 1);
                if (!protectedScriptedActionActive(fighter) && isValidEnemyTarget(fighter, fighter.currentTarget))
                {
                    PED::REGISTER_TARGET(fighter.ped, fighter.currentTarget, true);
                    AI::TASK_COMBAT_PED(fighter.ped, fighter.currentTarget, 0, 16);
                    fighter.lastTask = t;
                }
            }
        }
    }

    if (fighter.hardened && !boss && health > 0 && health < std::max(80, fighter.maxHealth / 5) && t - fighter.spawnedAt < 12000)
    {
        int restored = std::max(health, std::max(90, fighter.maxHealth / 4));
        ENTITY::SET_ENTITY_HEALTH(fighter.ped, restored, 0);
        health = restored;
    }

    bool meleeBattle = g_menu.battleType != BattleType::AllWeapons;
    DWORD healDelay = boss ?
        (meleeBattle ? g_settings.bossHealMeleeDelayMs : g_settings.bossHealGunDelayMs) :
        g_settings.regularHealDelayMs;
    DWORD healTick = boss ?
        (meleeBattle ? g_settings.bossHealMeleeTickMs : g_settings.bossHealGunTickMs) :
        g_settings.regularHealTickMs;
    if (fighter.heals && health > 0 && health < fighter.maxHealth && t - fighter.lastDamage > healDelay && t - fighter.lastHeal > healTick)
    {
        int healAmount = boss ? g_settings.bossHealAmount : std::max(g_settings.regularHealMinAmount, fighter.maxHealth / 35);
        int restored = std::min(fighter.maxHealth, health + healAmount);
        ENTITY::SET_ENTITY_HEALTH(fighter.ped, restored, 0);
        health = restored;
        fighter.lastHeal = t;
    }

    DWORD dynamicRepairMs = dynamicTuningRepairInterval();
    if (fighter.nextDynamicTuneRepairAt == 0)
        fighter.nextDynamicTuneRepairAt = t + dynamicRepairMs + static_cast<DWORD>((fighter.spawnIndex * 97) % 1800);
    if (t >= fighter.nextDynamicTuneRepairAt)
    {
        int healthBeforeTune = health;
        repairDynamicPedTuning(fighter, t);
        if (fighter.heals)
            clearVisibleDamage(fighter.ped);
        int tunedHealth = ENTITY::GET_ENTITY_HEALTH(fighter.ped);
        if (healthBeforeTune > 0 && tunedHealth > healthBeforeTune)
        {
            int preserved = std::min(healthBeforeTune, fighter.maxHealth);
            ENTITY::SET_ENTITY_HEALTH(fighter.ped, preserved, 0);
            health = preserved;
        }
        else if (tunedHealth > fighter.maxHealth)
        {
            ENTITY::SET_ENTITY_HEALTH(fighter.ped, fighter.maxHealth, 0);
            health = fighter.maxHealth;
        }
        else if (tunedHealth > 0)
        {
            health = tunedHealth;
        }
        fighter.nextDynamicTuneRepairAt = t + dynamicRepairMs + static_cast<DWORD>((fighter.spawnIndex * 97) % 1800);
    }

    fighter.lastHealth = health;
}

int aliveCountForTeam(int team)
{
    int count = 0;
    for (const Fighter& fighter : g_runtime.fighters)
    {
        if (fighter.team == team && isAlive(fighter))
            ++count;
    }
    if (team == g_runtime.playerTeam && playerAliveInBattle())
        ++count;
    return count;
}

int aliveFighterCount()
{
    int count = 0;
    for (const Fighter& fighter : g_runtime.fighters)
    {
        if (isAlive(fighter))
            ++count;
    }
    return count;
}

Fighter* firstAliveFighter()
{
    for (Fighter& fighter : g_runtime.fighters)
    {
        if (isAlive(fighter))
            return &fighter;
    }
    return nullptr;
}

Vec3 spectatorReferencePosition()
{
    Ped player = playerPed();
    if (exists(player))
        return entityCoords(player);

    return g_runtime.battleCenter;
}

bool spectatorIndexWithinDistance(int index)
{
    if (g_settings.spectatorMaxTargetDistance <= 0.0f)
        return true;

    if (index < 0 || index >= static_cast<int>(g_runtime.fighters.size()))
        return false;

    const Fighter& fighter = g_runtime.fighters[static_cast<size_t>(index)];
    if (!exists(fighter.ped))
        return false;

    float limit = g_settings.spectatorMaxTargetDistance;
    return distanceSquared(entityCoords(fighter.ped), spectatorReferencePosition()) <= limit * limit;
}

bool spectatorIndexSelectable(int index)
{
    return index >= 0 &&
        index < static_cast<int>(g_runtime.fighters.size()) &&
        isAlive(g_runtime.fighters[static_cast<size_t>(index)]) &&
        spectatorIndexWithinDistance(index);
}

Fighter* spectatorTarget()
{
    if (spectatorIndexSelectable(g_runtime.spectatorTargetIndex))
    {
        return &g_runtime.fighters[static_cast<size_t>(g_runtime.spectatorTargetIndex)];
    }
    return nullptr;
}

int nextAliveSpectatorIndex(int startAfter)
{
    int total = static_cast<int>(g_runtime.fighters.size());
    if (total <= 0)
        return -1;

    for (int offset = 1; offset <= total; ++offset)
    {
        int index = (startAfter + offset) % total;
        if (index < 0)
            index += total;
        if (spectatorIndexSelectable(index))
            return index;
    }
    return -1;
}

int previousAliveSpectatorIndex(int startBefore)
{
    int total = static_cast<int>(g_runtime.fighters.size());
    if (total <= 0)
        return -1;

    for (int offset = 1; offset <= total; ++offset)
    {
        int index = (startBefore - offset) % total;
        if (index < 0)
            index += total;
        if (spectatorIndexSelectable(index))
            return index;
    }
    return -1;
}

bool spectatorIndexAlive(int index)
{
    return spectatorIndexSelectable(index);
}

void makePlayerBattleSpectator()
{
    if (g_runtime.playerSpectating)
    {
        hidePlayerForBattleSpectator();
        return;
    }

    g_runtime.playerSpectating = true;
    g_runtime.playerParticipating = false;
    if (!g_runtime.playerEliminated)
        g_runtime.playerTeam = -1;
    if (g_runtime.freeForAll)
        g_runtime.freeForAllSpectate = true;
    hidePlayerForBattleSpectator();

    markRelationshipsDirty();
    updateRelationshipsIfNeeded(now());
    for (Fighter& fighter : g_runtime.fighters)
    {
        if (exists(fighter.ped))
            applyDamagePermissions(fighter);
        removeFighterBlip(fighter);
        ensureFighterBlip(fighter);
    }
}

void ensureSpectatorCamera()
{
    if (g_runtime.spectatorCameraActive &&
        g_runtime.spectatorCam &&
        CAM::DOES_CAM_EXIST(g_runtime.spectatorCam))
    {
        return;
    }

    g_runtime.spectatorCam = CAM::CREATE_CAM(const_cast<char*>("DEFAULT_SCRIPTED_CAMERA"), true);
    if (!g_runtime.spectatorCam || !CAM::DOES_CAM_EXIST(g_runtime.spectatorCam))
        return;

    CAM::SET_CAM_FOV(g_runtime.spectatorCam, 54.0f);
    CAM::SET_CAM_NEAR_CLIP(g_runtime.spectatorCam, 0.1f);
    CAM::SET_CAM_ACTIVE(g_runtime.spectatorCam, true);
    CAM::RENDER_SCRIPT_CAMS(true, true, 350, true, true, 0);
    g_runtime.spectatorCameraActive = true;
}

void stopSpectatorCamera()
{
    if (g_runtime.spectatorCameraActive || g_runtime.spectatorCam)
    {
        CAM::RENDER_SCRIPT_CAMS(false, true, 250, true, true, 0);
        if (g_runtime.spectatorCam && CAM::DOES_CAM_EXIST(g_runtime.spectatorCam))
            CAM::DESTROY_CAM(g_runtime.spectatorCam, false);
    }

    STREAMING::CLEAR_FOCUS();
    restorePlayerAfterBattleSpectator();
    if (g_runtime.spectatorControlOverride)
    {
        PLAYER::SET_PLAYER_CONTROL(PLAYER::PLAYER_ID(), true, 0, false);
        PLAYER::SET_PLAYER_INVINCIBLE(PLAYER::PLAYER_ID(), false);
    }
    g_runtime.spectatorCameraActive = false;
    g_runtime.spectatorControlOverride = false;
    g_runtime.spectatorCameraSmoothed = false;
    g_runtime.spectatorCam = 0;
    g_runtime.spectatorTargetIndex = -1;
    g_runtime.preferredSpectatorTargetIndex = -1;
    g_runtime.spectatorCameraLastTargetIndex = -1;
}

void updateSpectatorCamera(DWORD t)
{
    if (!g_runtime.battleActive)
    {
        if (g_runtime.spectatorCameraActive || g_runtime.spectatorCam)
            stopSpectatorCamera();
        else
            restorePlayerAfterBattleSpectator();
        deletePlayerBattleCorpse();
        return;
    }

    if (!g_runtime.spectatorCameraActive)
        return;

    Fighter* target = spectatorTarget();
    if (!target)
    {
        int next = nextAliveSpectatorIndex(g_runtime.spectatorTargetIndex);
        if (next < 0)
        {
            stopSpectatorCamera();
            return;
        }
        g_runtime.spectatorTargetIndex = next;
        g_runtime.spectatorCameraSmoothed = false;
        target = spectatorTarget();
    }

    if (!target || !exists(target->ped))
    {
        stopSpectatorCamera();
        return;
    }

    ensureSpectatorCamera();
    if (!g_runtime.spectatorCameraActive)
        return;

    keepPlayerNearSpectatorTarget(*target, t);

    Vec3 self = entityCoords(target->ped);
    STREAMING::REQUEST_COLLISION_AT_COORD(self.x, self.y, self.z);
    PATHFIND::ADD_NAVMESH_REQUIRED_REGION(self.x, self.y, 18.0f);

    Vector3 forward = ENTITY::GET_ENTITY_FORWARD_VECTOR(target->ped);
    Vec3 bodyLook{ self.x, self.y, self.z + 0.82f };
    Vec3 desiredLook{
        bodyLook.x + forward.x * 7.5f,
        bodyLook.y + forward.y * 7.5f,
        bodyLook.z + 0.10f
    };
    Vec3 desiredPos = fromNative(ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(target->ped, 0.0f, -4.45f, 1.62f));

    if (!g_runtime.spectatorCameraSmoothed ||
        g_runtime.spectatorCameraLastTargetIndex != g_runtime.spectatorTargetIndex ||
        distanceSquared(g_runtime.spectatorCameraPos, desiredPos) > 55.0f * 55.0f)
    {
        g_runtime.spectatorCameraPos = desiredPos;
        g_runtime.spectatorCameraLookAt = desiredLook;
        g_runtime.spectatorCameraSmoothed = true;
        g_runtime.spectatorCameraLastTargetIndex = g_runtime.spectatorTargetIndex;
    }
    else
    {
        g_runtime.spectatorCameraPos = lerpVec3(g_runtime.spectatorCameraPos, desiredPos, 0.13f);
        g_runtime.spectatorCameraLookAt = lerpVec3(g_runtime.spectatorCameraLookAt, desiredLook, 0.18f);
    }

    CAM::SET_CAM_COORD(
        g_runtime.spectatorCam,
        g_runtime.spectatorCameraPos.x,
        g_runtime.spectatorCameraPos.y,
        g_runtime.spectatorCameraPos.z);
    CAM::POINT_CAM_AT_COORD(
        g_runtime.spectatorCam,
        g_runtime.spectatorCameraLookAt.x,
        g_runtime.spectatorCameraLookAt.y,
        g_runtime.spectatorCameraLookAt.z);
    STREAMING::SET_FOCUS_ENTITY(target->ped);

    PLAYER::SET_PLAYER_CONTROL(PLAYER::PLAYER_ID(), false, 0, false);
    PLAYER::SET_PLAYER_INVINCIBLE(PLAYER::PLAYER_ID(), true);
    g_runtime.spectatorControlOverride = true;
}

void selectSpectatorCameraTarget(int direction)
{
    if (!g_runtime.battleActive || g_runtime.fighters.empty())
        return;

    makePlayerBattleSpectator();
    int next = -1;
    if (!g_runtime.spectatorCameraActive &&
        spectatorIndexAlive(g_runtime.preferredSpectatorTargetIndex))
    {
        next = g_runtime.preferredSpectatorTargetIndex;
    }
    else
    {
        next = direction < 0 ?
            previousAliveSpectatorIndex(g_runtime.spectatorTargetIndex) :
            nextAliveSpectatorIndex(g_runtime.spectatorTargetIndex);
    }

    if (next < 0)
    {
        setStatus("No nearby living fighters to spectate", 3500);
        stopSpectatorCamera();
        return;
    }

    g_runtime.spectatorTargetIndex = next;
    g_runtime.spectatorCameraSmoothed = false;
    if (next == g_runtime.preferredSpectatorTargetIndex)
        g_runtime.preferredSpectatorTargetIndex = -1;
    ensureSpectatorCamera();
    updateSpectatorCamera(now());

    Fighter* target = spectatorTarget();
    if (target)
        setStatus("Spectating " + target->displayName, 3500);
}

void cycleSpectatorCamera()
{
    selectSpectatorCameraTarget(1);
}

void toggleSpectatorCamera()
{
    if (!g_runtime.battleActive || g_runtime.fighters.empty())
        return;

    if (g_runtime.spectatorCameraActive)
    {
        stopSpectatorCamera();
        setStatus("Spectator camera off", 3500);
        return;
    }

    selectSpectatorCameraTarget(1);
}

int aliveBattleRoyaleGroupCount()
{
    std::vector<Hash> aliveGroups;
    aliveGroups.reserve(g_runtime.fighters.size() + 1);

    if (playerAliveInBattle() && g_runtime.playerFreeForAllGroup)
        aliveGroups.push_back(g_runtime.playerFreeForAllGroup);

    for (const Fighter& fighter : g_runtime.fighters)
    {
        if (!isAlive(fighter) || !fighter.group)
            continue;

        if (std::find(aliveGroups.begin(), aliveGroups.end(), fighter.group) == aliveGroups.end())
            aliveGroups.push_back(fighter.group);
    }
    return static_cast<int>(aliveGroups.size());
}

Hash firstAliveBattleRoyaleGroup()
{
    if (playerAliveInBattle() && g_runtime.playerFreeForAllGroup)
        return g_runtime.playerFreeForAllGroup;

    for (const Fighter& fighter : g_runtime.fighters)
    {
        if (isAlive(fighter) && fighter.group)
            return fighter.group;
    }
    return 0;
}

int activeConfiguredTeams()
{
    int count = 0;
    for (const TeamSetup& team : g_teams)
    {
        if (teamEnabled(team))
            ++count;
    }
    return count;
}

bool anyHostileTeamConfigured()
{
    for (const TeamSetup& team : g_teams)
    {
        if (teamEnabled(team) && team.playerRelation == PlayerRelation::Hostile)
            return true;
    }
    return false;
}

int requestedFighterCount()
{
    int count = 0;
    if (g_runtime.freeForAll || freeForAllSelected())
    {
        for (const TeamRosterSlot& slot : g_battleRoyaleSets)
            count += effectiveSlotCount(slot);
        return count;
    }

    for (const TeamSetup& team : g_teams)
    {
        for (const TeamRosterSlot& slot : team.sets)
            count += effectiveSlotCount(slot);
    }
    return count;
}

int spawnedTeamCount()
{
    std::array<bool, kTeamCount> spawned{};
    for (const Fighter& fighter : g_runtime.fighters)
    {
        if (exists(fighter.ped) && fighter.team >= 0 && fighter.team < kTeamCount)
            spawned[static_cast<size_t>(fighter.team)] = true;
    }

    int count = 0;
    for (bool hasTeam : spawned)
    {
        if (hasTeam)
            ++count;
    }
    return count;
}

bool spawnedHostileTeamExists()
{
    for (const Fighter& fighter : g_runtime.fighters)
    {
        if (exists(fighter.ped) &&
            fighter.team >= 0 &&
            fighter.team < kTeamCount &&
            g_teams[static_cast<size_t>(fighter.team)].playerRelation == PlayerRelation::Hostile)
        {
            return true;
        }
    }
    return false;
}

int deathmatchKillLimit()
{
    return clampDeathmatchKillLimitValue(g_menu.killLimit);
}

int teamKillScore(int team)
{
    int score = 0;
    if (g_runtime.playerWasParticipant && g_runtime.playerTeam == team)
        score += g_runtime.playerKills;

    for (const Fighter& fighter : g_runtime.fighters)
    {
        if (fighter.team == team)
            score += fighter.kills;
    }
    return score;
}

int teamDeathScore(int team)
{
    int deaths = 0;
    if (g_runtime.playerWasParticipant && g_runtime.playerTeam == team)
        deaths += g_runtime.playerDeaths;

    for (const Fighter& fighter : g_runtime.fighters)
    {
        if (fighter.team == team)
            deaths += fighter.deaths;
    }
    return deaths;
}

int groupKillScore(Hash group)
{
    int score = 0;
    if (group && g_runtime.playerWasParticipant && g_runtime.playerFreeForAllGroup == group)
        score += g_runtime.playerKills;

    for (const Fighter& fighter : g_runtime.fighters)
    {
        if (fighter.group == group)
            score += fighter.kills;
    }
    return score;
}

int groupDeathScore(Hash group)
{
    int deaths = 0;
    if (group && g_runtime.playerWasParticipant && g_runtime.playerFreeForAllGroup == group)
        deaths += g_runtime.playerDeaths;

    for (const Fighter& fighter : g_runtime.fighters)
    {
        if (fighter.group == group)
            deaths += fighter.deaths;
    }
    return deaths;
}

float kdRatio(int kills, int deaths)
{
    return deaths <= 0 ? static_cast<float>(kills) : static_cast<float>(kills) / static_cast<float>(deaths);
}

std::string kdText(int kills, int deaths)
{
    char buffer[24]{};
    std::snprintf(buffer, sizeof(buffer), "%.2f", kdRatio(kills, deaths));
    return buffer;
}

int bestFreeForAllDeathmatchScore()
{
    int best = g_runtime.playerWasParticipant ? g_runtime.playerKills : 0;
    if (g_runtime.freeForAllTeamSize > 1)
    {
        std::vector<Hash> groups;
        if (g_runtime.playerFreeForAllGroup)
            groups.push_back(g_runtime.playerFreeForAllGroup);
        for (const Fighter& fighter : g_runtime.fighters)
        {
            if (fighter.group && std::find(groups.begin(), groups.end(), fighter.group) == groups.end())
                groups.push_back(fighter.group);
        }

        for (Hash group : groups)
            best = std::max(best, groupKillScore(group));
        return best;
    }

    for (const Fighter& fighter : g_runtime.fighters)
        best = std::max(best, fighter.kills);
    return best;
}

std::string freeForAllDeathmatchScoreText()
{
    int limit = deathmatchKillLimit();
    int leaderScore = bestFreeForAllDeathmatchScore();
    bool playerInMatch = g_runtime.playerWasParticipant && !g_runtime.freeForAllSpectate;
    int playerScore = g_runtime.freeForAllTeamSize > 1 ?
        groupKillScore(g_runtime.playerFreeForAllGroup) :
        g_runtime.playerKills;

    char buffer[144]{};
    if (limit <= 0)
    {
        if (playerInMatch)
        {
            std::snprintf(
                buffer,
                sizeof(buffer),
                "%s:%d  %s:%d",
                g_runtime.freeForAllTeamSize > 1 ? "Your squad" : "You",
                playerScore,
                g_runtime.freeForAllTeamSize > 1 ? "Best squad" : "Leader",
                leaderScore);
        }
        else
        {
            std::snprintf(
                buffer,
                sizeof(buffer),
                "%s:%d",
                g_runtime.freeForAllTeamSize > 1 ? "Best squad" : "Leader",
                leaderScore);
        }
        return buffer;
    }

    if (playerInMatch)
    {
        std::snprintf(
            buffer,
            sizeof(buffer),
            "%s:%d/%d  %s:%d/%d",
            g_runtime.freeForAllTeamSize > 1 ? "Your squad" : "You",
            playerScore,
            limit,
            g_runtime.freeForAllTeamSize > 1 ? "Best squad" : "Leader",
            leaderScore,
            limit);
    }
    else
    {
        std::snprintf(
            buffer,
            sizeof(buffer),
            "%s:%d/%d",
            g_runtime.freeForAllTeamSize > 1 ? "Best squad" : "Leader",
            leaderScore,
            limit);
    }
    return buffer;
}

std::string battleSummaryText()
{
    if (g_runtime.startCountdownActive)
    {
        int seconds = startCountdownRemainingSeconds();
        if (seconds <= 0)
            return "Fight!";

        char buffer[64]{};
        std::snprintf(buffer, sizeof(buffer), "Battle starts in %d", seconds);
        return buffer;
    }

    if (deathmatchActive())
    {
        int limit = deathmatchKillLimit();
        char buffer[144]{};
        if (g_runtime.freeForAll)
        {
            std::snprintf(buffer, sizeof(buffer), "Score - %s", freeForAllDeathmatchScoreText().c_str());
            return buffer;
        }

        std::snprintf(
            buffer,
            sizeof(buffer),
            "Score - T1:%d/%d  T2:%d/%d  T3:%d/%d  T4:%d/%d",
            teamKillScore(0), limit,
            teamKillScore(1), limit,
            teamKillScore(2), limit,
            teamKillScore(3), limit);
        return buffer;
    }

    if (freeForAllActive())
    {
        char buffer[96]{};
        int aliveCombatants = aliveFighterCount() + (playerAliveInBattle() ? 1 : 0);
        if (g_runtime.freeForAllTeamSize > 1)
        {
            std::snprintf(
                buffer,
                sizeof(buffer),
                "Alive - Battle Royale:%d  Teams:%d",
                aliveCombatants,
                aliveBattleRoyaleGroupCount());
        }
        else
        {
            std::snprintf(
                buffer,
                sizeof(buffer),
                "Alive - Battle Royale:%d",
                aliveCombatants);
        }
        return buffer;
    }

    char buffer[128]{};
    std::snprintf(
        buffer,
        sizeof(buffer),
        "Alive - T1:%d  T2:%d  T3:%d  T4:%d",
        aliveCountForTeam(0),
        aliveCountForTeam(1),
        aliveCountForTeam(2),
        aliveCountForTeam(3));
    return buffer;
}

std::string freeForAllGroupName(Hash group)
{
    if (group && group == g_runtime.playerFreeForAllGroup)
        return g_runtime.freeForAllTeamSize > 1 ? "Arthur's squad" : playerLeaderboardName();

    for (const Fighter& fighter : g_runtime.fighters)
    {
        if (fighter.group == group)
            return g_runtime.freeForAllTeamSize > 1 ? fighter.displayName + "'s squad" : fighter.displayName;
    }

    return g_runtime.freeForAllTeamSize > 1 ? "Unknown squad" : "Unknown fighter";
}

void finishDeathmatchBattle(const std::string& status)
{
    g_runtime.battleActive = false;
    g_runtime.resultAnnounced = true;
    refillPlayerHealthAndCoresIfAlive();
    markRelationshipsDirty();
    updateRelationshipsIfNeeded(now());
    for (Fighter& fighter : g_runtime.fighters)
    {
        if (isAlive(fighter))
            AI::CLEAR_PED_TASKS(fighter.ped, true, false);
        removeFighterBlip(fighter);
        ensureFighterBlip(fighter);
    }
    setStatus(status, 11000);
}

bool announceDeathmatchResultIfFinished()
{
    if (!deathmatchActive() || g_runtime.resultAnnounced)
        return false;

    int limit = deathmatchKillLimit();
    if (limit <= 0)
        return false;

    if (!g_runtime.freeForAll)
    {
        int winner = -1;
        int winningScore = -1;
        for (int team = 0; team < kTeamCount; ++team)
        {
            int score = teamKillScore(team);
            if (score >= limit && score > winningScore)
            {
                winner = team;
                winningScore = score;
            }
        }

        if (winner >= 0)
        {
            char buffer[112]{};
            std::snprintf(buffer, sizeof(buffer), "Team Deathmatch finished: Team %d wins with %d kills", winner + 1, winningScore);
            finishDeathmatchBattle(buffer);
            return true;
        }
        return false;
    }

    if (g_runtime.freeForAllTeamSize > 1)
    {
        std::vector<Hash> groups;
        if (g_runtime.playerFreeForAllGroup)
            groups.push_back(g_runtime.playerFreeForAllGroup);
        for (const Fighter& fighter : g_runtime.fighters)
        {
            if (fighter.group && std::find(groups.begin(), groups.end(), fighter.group) == groups.end())
                groups.push_back(fighter.group);
        }

        Hash winningGroup = 0;
        int winningScore = -1;
        for (Hash group : groups)
        {
            int score = groupKillScore(group);
            if (score >= limit && score > winningScore)
            {
                winningGroup = group;
                winningScore = score;
            }
        }

        if (winningGroup)
        {
            finishDeathmatchBattle("Free For All finished: " + freeForAllGroupName(winningGroup) + " wins with " + std::to_string(winningScore) + " kills");
            return true;
        }
        return false;
    }

    std::string winnerName;
    int winningScore = -1;
    if (g_runtime.playerWasParticipant && g_runtime.playerKills >= limit)
    {
        winnerName = playerLeaderboardName();
        winningScore = g_runtime.playerKills;
    }

    for (const Fighter& fighter : g_runtime.fighters)
    {
        if (fighter.kills >= limit && fighter.kills > winningScore)
        {
            winnerName = fighter.displayName;
            winningScore = fighter.kills;
        }
    }

    if (!winnerName.empty())
    {
        finishDeathmatchBattle("Free For All finished: " + winnerName + " wins with " + std::to_string(winningScore) + " kills");
        return true;
    }

    return false;
}

void announceResultIfFinished()
{
    if (!g_runtime.battleActive)
        return;

    if (g_runtime.deathmatch)
    {
        announceDeathmatchResultIfFinished();
        return;
    }

    if (freeForAllActive())
    {
        int aliveFighters = aliveFighterCount();
        bool playerAlive = playerAliveInBattle();
        int livingCombatants = aliveFighters + (playerAlive ? 1 : 0);
        int livingGroups = aliveBattleRoyaleGroupCount();
        if (livingGroups > 1)
            return;

        g_runtime.battleActive = false;
        g_runtime.resultAnnounced = true;
        refillPlayerHealthAndCoresIfAlive();
        markRelationshipsDirty();
        updateRelationshipsIfNeeded(now());

        if (livingCombatants == 0)
        {
            setStatus("Battle Royale finished: no survivors", 9000);
            return;
        }

        Hash winningGroup = firstAliveBattleRoyaleGroup();
        if (playerAlive && winningGroup && winningGroup == g_runtime.playerFreeForAllGroup)
        {
            setStatus(g_runtime.freeForAllTeamSize > 1 ? "Battle Royale finished: Arthur's squad wins" : "Battle Royale finished: Arthur Morgan wins", 11000);
            return;
        }

        Fighter* winner = nullptr;
        for (Fighter& fighter : g_runtime.fighters)
        {
            if (isAlive(fighter) && (!winningGroup || fighter.group == winningGroup))
            {
                winner = &fighter;
                break;
            }
        }

        if (winner)
        {
            for (Fighter& fighter : g_runtime.fighters)
            {
                if (isAlive(fighter) && fighter.group == winner->group)
                    AI::CLEAR_PED_TASKS(fighter.ped, true, false);
            }
            std::string status = g_runtime.freeForAllTeamSize > 1 ?
                "Battle Royale finished: " + winner->displayName + "'s squad wins" :
                "Battle Royale finished: " + winner->displayName + " wins";
            setStatus(status, 11000);
        }
        return;
    }

    std::array<int, kTeamCount> alive{};
    int livingTeams = 0;
    int winner = -1;
    for (int i = 0; i < kTeamCount; ++i)
    {
        alive[i] = aliveCountForTeam(i);
        if (alive[i] > 0)
        {
            ++livingTeams;
            winner = i;
        }
    }

    if (livingTeams == 0)
    {
        g_runtime.battleActive = false;
        g_runtime.resultAnnounced = true;
        refillPlayerHealthAndCoresIfAlive();
        markRelationshipsDirty();
        updateRelationshipsIfNeeded(now());
        setStatus("Battle finished: no survivors", 9000);
        return;
    }

    if (g_runtime.resultAnnounced)
        return;

    if (livingTeams == 1)
    {
        bool winnerHostileToPlayer = runtimeRelationToPlayer(winner) == PlayerRelation::Hostile;
        bool startedAsHostileWave = g_runtime.initialActiveTeams == 1 && winnerHostileToPlayer;
        if (winnerHostileToPlayer)
        {
            if (!startedAsHostileWave)
            {
                char buffer[112]{};
                std::snprintf(buffer, sizeof(buffer), "Team %d won; survivors are still hostile", winner + 1);
                setStatus(buffer, 10000);
            }
            g_runtime.resultAnnounced = true;
            markRelationshipsDirty();
            updateRelationshipsIfNeeded(now());
            return;
        }

        g_runtime.battleActive = false;
        g_runtime.resultAnnounced = true;
        refillPlayerHealthAndCoresIfAlive();
        markRelationshipsDirty();
        updateRelationshipsIfNeeded(now());
        char buffer[96]{};
        std::snprintf(buffer, sizeof(buffer), "Battle finished: Team %d wins with %d left", winner + 1, alive[winner]);
        setStatus(buffer, 11000);

        for (Fighter& fighter : g_runtime.fighters)
        {
            if (fighter.team == winner && isAlive(fighter) && runtimeRelationToPlayer(winner) != PlayerRelation::Hostile)
                AI::CLEAR_PED_TASKS(fighter.ped, true, false);
        }
    }
}

bool tooFarFromPlayer()
{
    if (g_runtime.fighters.empty())
        return false;
    if (g_runtime.playerRevivePending)
        return false;
    if (g_runtime.playerSpectating || g_runtime.spectatorCameraActive)
        return false;

    Vec3 player = entityCoords(playerPed());
    float limit = g_settings.cleanupDistance * g_settings.cleanupDistance;
    for (const Fighter& fighter : g_runtime.fighters)
    {
        if (exists(fighter.ped) && distanceSquared(player, entityCoords(fighter.ped)) < limit)
            return false;
    }
    return true;
}

void eliminatePlayerFromBattle()
{
    if (g_runtime.playerEliminated)
        return;

    recordPlayerKilledByNpc();
    recordPlayerEliminationPosition();
    g_runtime.playerEliminated = true;
    g_runtime.playerParticipating = false;
    schedulePlayerBattleRevive(now());
    markRelationshipsDirty();
    updateRelationshipsIfNeeded(now());
    for (Fighter& fighter : g_runtime.fighters)
    {
        if (exists(fighter.ped))
            applyDamagePermissions(fighter);
        removeFighterBlip(fighter);
        ensureFighterBlip(fighter);
    }
    setStatus("You are out of the battle - spectator mode", 8000);
}

void handleDeathmatchPlayerDeath()
{
    if (g_runtime.playerRevivePending)
        return;

    recordPlayerKilledByNpc();
    ++g_runtime.playerDeaths;
    g_runtime.playerEliminated = true;
    schedulePlayerBattleRevive(now());
    markRelationshipsDirty();
    updateRelationshipsIfNeeded(now());
    setStatus("Respawning...", 4500);
}

void updatePlayerParticipation()
{
    if (!g_runtime.battleActive)
        return;

    Ped player = playerPed();
    bool dead = !exists(player) ||
        PLAYER::IS_PLAYER_DEAD(PLAYER::PLAYER_ID()) ||
        PED::IS_PED_DEAD_OR_DYING(player, true) ||
        PED::IS_PED_FATALLY_INJURED(player);
    updatePlayerDamageAttribution(dead);

    if (!dead)
    {
        if (!g_runtime.playerEliminated)
            rememberPlayerSafePosition();
        return;
    }

    if (deathmatchActive() && g_runtime.playerWasParticipant)
    {
        handleDeathmatchPlayerDeath();
        return;
    }

    if (!g_runtime.playerEliminated)
        eliminatePlayerFromBattle();
    else
        schedulePlayerBattleRevive(now());
}

void holdFighterForStartCountdown(Fighter& fighter, DWORD t)
{
    if (!isAlive(fighter) || !exists(fighter.ped))
        return;

    fighter.currentTarget = 0;
    fighter.currentTargetStartedAt = 0;
    if (t - fighter.lastTask > 700u)
    {
        AI::CLEAR_PED_TASKS(fighter.ped, true, false);
        AI::TASK_STAND_STILL(fighter.ped, 1200);
        fighter.lastTask = t;
        fighter.lastRepositionTask = t;
        fighter.lastShotTask = t;
    }
}

void releaseStartCountdown(DWORD t)
{
    if (!g_runtime.startCountdownActive)
        return;

    g_runtime.startCountdownActive = false;
    g_runtime.startCountdownEndsAt = 0;
    bool stagedFreeForAllRelationshipsReady = g_runtime.freeForAll && !g_runtime.relationshipsDirty;
    if (!stagedFreeForAllRelationshipsReady)
    {
        markRelationshipsDirty();
        updateRelationshipsIfNeeded(t);
    }
    for (Fighter& fighter : g_runtime.fighters)
    {
        if (!isAlive(fighter) || !exists(fighter.ped))
            continue;

        ENTITY::FREEZE_ENTITY_POSITION(fighter.ped, false);
        AI::CLEAR_PED_TASKS(fighter.ped, true, false);
        fighter.lastTask = 0;
        fighter.lastRepositionTask = 0;
        fighter.lastShotTask = 0;
        fighter.currentTarget = 0;
        fighter.currentTargetStartedAt = 0;
        resetIdleWatchdogState(fighter, t, 0);
        repairDynamicPedTuning(fighter, t);
        readyWeapon(fighter, t, true);
        taskFighter(fighter, t, true);
    }
    setStatus("Fight!", 2500);
}

bool updateStartCountdown(DWORD t)
{
    if (!g_runtime.startCountdownActive)
        return false;

    if (t >= g_runtime.startCountdownEndsAt)
    {
        releaseStartCountdown(t);
        return false;
    }

    for (Fighter& fighter : g_runtime.fighters)
        holdFighterForStartCountdown(fighter, t);
    return true;
}

DWORD fighterPhaseOffset(const Fighter& fighter, DWORD interval, DWORD salt)
{
    if (interval == 0)
        return 0;

    DWORD stable = static_cast<DWORD>(
        std::max(0, fighter.spawnIndex) * 37 +
        std::max(0, fighter.team) * 53 +
        static_cast<int>(fighter.difficulty) * 71);
    return (stable + salt) % interval;
}

bool largeDeathmatchActive()
{
    return deathmatchActive() &&
        static_cast<int>(g_runtime.fighters.size()) >= g_settings.largeDeathmatchThreshold;
}

DWORD dynamicTuningRepairInterval()
{
    return largeDeathmatchActive() ? g_settings.largeDeathmatchDynamicRepairMs : kDynamicTuningRepairMs;
}

DWORD fighterBlipValidationInterval()
{
    return largeDeathmatchActive() ? g_settings.largeDeathmatchBlipValidationMs : kBlipValidationMs;
}

DWORD fighterMaintenanceInterval(const Fighter& fighter)
{
    return isEnhancedFighter(fighter) ? kEliteMaintenanceMs : kNormalMaintenanceMs;
}

DWORD fighterCombatInterval(const Fighter& fighter)
{
    if (largeDeathmatchActive() && !isEnhancedFighter(fighter))
        return g_settings.largeDeathmatchCombatUpdateMs;
    return isEnhancedFighter(fighter) ? kEliteCombatUpdateMs : kNormalCombatUpdateMs;
}

void seedFighterUpdateSchedule(Fighter& fighter, DWORD t)
{
    fighter.nextMaintenanceAt = t + fighterPhaseOffset(fighter, fighterMaintenanceInterval(fighter), 11);
    fighter.nextCombatUpdateAt = t + fighterPhaseOffset(fighter, fighterCombatInterval(fighter), 23);
    fighter.nextBlipCheckAt = t + fighterPhaseOffset(fighter, fighterBlipValidationInterval(), 47);
    fighter.nextDynamicTuneRepairAt = t + dynamicTuningRepairInterval() + fighterPhaseOffset(fighter, 1800u, 89);
    fighter.nextGroupValidationAt = t + fighterPhaseOffset(fighter, kRelationshipValidationMs, 101);
}

void refreshFighterSnapshots(DWORD t)
{
    if (g_runtime.nextFighterSnapshotRefreshAt != 0 && t < g_runtime.nextFighterSnapshotRefreshAt)
        return;

    g_runtime.nextFighterSnapshotRefreshAt = t + g_settings.deathmatchSnapshotRefreshMs;
    g_runtime.fighterSnapshots.clear();
    g_runtime.fighterSnapshots.reserve(g_runtime.fighters.size());
    ++g_runtime.fighterSnapshotRefreshes;
    for (int i = 0; i < static_cast<int>(g_runtime.fighters.size()); ++i)
    {
        const Fighter& fighter = g_runtime.fighters[static_cast<size_t>(i)];
        bool alive = isAlive(fighter);
        if (!alive)
            continue;

        FighterSnapshot snapshot{};
        snapshot.ped = fighter.ped;
        snapshot.position = entityCoords(fighter.ped);
        snapshot.group = fighter.group;
        snapshot.team = fighter.team;
        snapshot.fighterIndex = i;
        snapshot.alive = true;
        snapshot.targetable = true;
        g_runtime.fighterSnapshots.push_back(snapshot);
    }
}

bool fighterNeedsCriticalMaintenance(const Fighter& fighter, DWORD t)
{
    if (!exists(fighter.ped))
        return true;
    if (fighter.respawnAt != 0 && t >= fighter.respawnAt)
        return true;
    if (fighter.cinematicRecoveryActive)
        return true;
    if (fighter.scriptedActionType != ScriptedActionType::None || fighter.scriptedActionResumeAt != 0)
        return true;
    if (shouldPollManagedWeapon(fighter, t))
        return true;
    if (fighter.crouchUntil != 0 && t >= fighter.crouchUntil)
        return true;
    return false;
}

bool fighterNeedsCriticalCombatUpdate(const Fighter& fighter, DWORD t)
{
    if (fighter.scriptedActionType != ScriptedActionType::None || fighter.scriptedActionResumeAt != 0)
        return true;
    if (shouldPollManagedWeapon(fighter, t))
        return true;
    return false;
}

void updateBattle()
{
    if (g_runtime.fighters.empty())
        return;

    DWORD t = now();
    g_runtime.deathmatchRespawnsThisFrame = 0;
    g_runtime.fullRetargetsThisFrame = 0;
    updatePlayerParticipation();
    suppressBattleRespawnThisFrame();
    revivePlayerAtBattleSpot(t);
    keepScreenVisibleAfterBattleRevive(t);
    if (g_settings.neverWantedDuringBattles)
        suppressWantedDuringBattle();
    else
        restoreWantedAfterBattle();

    if (g_runtime.nextCleanupDistanceCheck == 0 || t >= g_runtime.nextCleanupDistanceCheck)
    {
        g_runtime.nextCleanupDistanceCheck = t + 1000u;
        if (tooFarFromPlayer())
        {
            if (!distantBattleSimulationCanKeepBattleAlive())
            {
                clearBattle();
                setStatus("Battle cleared because it was too far away", 7000);
                return;
            }
        }
    }

    updateRelationshipsIfNeeded(t);
    validateRelationshipGroupAssignments(t);
    refreshFighterSnapshots(t);

    for (Fighter& fighter : g_runtime.fighters)
    {
        if (fighterNeedsCriticalMaintenance(fighter, t) || t >= fighter.nextMaintenanceAt)
        {
            maintainFighter(fighter);
            fighter.nextMaintenanceAt = t + fighterMaintenanceInterval(fighter);
        }

        if (t >= fighter.nextBlipCheckAt)
        {
            ensureFighterBlip(fighter);
            fighter.nextBlipCheckAt = t + fighterBlipValidationInterval();
        }
    }

    updateDeathmatchRespawnSystem(t);
#if BATTLECREATOR_ENABLE_DEATHMATCH_DIAGNOSTICS
    emitDeathmatchDiagnostics(t);
#endif

    if (updateStartCountdown(t))
        return;

    updateDistantBattleSimulation(t);
    if (!g_runtime.battleActive)
    {
        announceResultIfFinished();
        return;
    }

    if (g_runtime.battleActive)
    {
        for (Fighter& fighter : g_runtime.fighters)
        {
            if (fighterNeedsCriticalCombatUpdate(fighter, t) || t >= fighter.nextCombatUpdateAt)
            {
                taskFighter(fighter, t, false);
                fighter.nextCombatUpdateAt = t + fighterCombatInterval(fighter);
            }
        }
    }

    announceResultIfFinished();
}

bool spawnFighterFromSlot(const TeamRosterSlot& slot, int teamIndex, int spawnIndex)
{
    bool boss = slot.difficulty == Difficulty::Bosses;
    bool special = slot.difficulty == Difficulty::Special;
    Hash model{};
    const char* voice = nullptr;
    const NamedPedDef* namedPed = nullptr;
    const SpecialPedDef* specialPed = nullptr;

    if (boss)
    {
        const BossDef& bossDef = kBosses[static_cast<size_t>(slot.boss)];
        model = requestAnyBossModel(bossDef, spawnIndex);
        voice = bossDef.voice;
    }
    else if (special)
    {
        specialPed = &kSpecialPeds[static_cast<size_t>(slot.special)];
        if (namedCharacterAlreadySpawned(specialPed->name))
            return false;
        model = requestAnySpecialPedModel(*specialPed);
        voice = specialPed->voice;
    }
    else if (isUniqueNamedPedSet(slot.pedSet))
    {
        model = requestUniqueNamedPedModel(slot.pedSet, spawnIndex, namedPed);
        if (namedPed)
            voice = namedPed->voice;
    }
    else
    {
        const PedSet& pedSet = g_pedSets[static_cast<size_t>(slot.pedSet)];
        model = requestAnyModel(pedSet.models, spawnIndex);
    }

    if (!model)
        return false;
    STREAMING::REQUEST_COLLISION_FOR_MODEL(model);

    Vec3 pos{};
    float heading{};
    Ped ped{};
    for (int attempt = 0; attempt < kSpawnCreateAttempts; ++attempt)
    {
        if (!resolveSpawnSlotPosition(teamIndex, spawnIndex, attempt, pos))
        {
            if (battleSpawnDistance() >= kSpawnInwardFallbackDistance && attempt > 0 && attempt % 8 == 0)
                WAIT(0);
            continue;
        }

        heading = g_runtime.freeForAll ?
            headingToward(pos, g_runtime.battleCenter) :
            std::fmod(formationForwardForTeam(teamIndex) * (180.0f / kPi), 360.0f);
        if (heading < 0.0f)
            heading += 360.0f;

        STREAMING::REQUEST_COLLISION_AT_COORD(pos.x, pos.y, pos.z);
        PATHFIND::ADD_NAVMESH_REQUIRED_REGION(pos.x, pos.y, 10.0f);
        if (battleSpawnDistance() >= kSpawnInwardFallbackDistance && attempt > 0 && attempt % 6 == 0)
            WAIT(0);

        ped = PED::CREATE_PED(model, pos.x, pos.y, pos.z, heading, true, true, true, true);
        if (exists(ped))
            break;
    }
    STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);
    if (!exists(ped))
        return false;

    Hash relationshipGroup = g_runtime.freeForAll ?
        g_runtime.freeForAllSpawnGroup :
        g_runtime.groups[static_cast<size_t>(teamIndex)];
    if (!relationshipGroup)
    {
        if (g_runtime.freeForAll)
            relationshipGroup = g_runtime.freeForAllSpawnGroup = createFreeForAllRelationshipGroup(99998);
        if (!relationshipGroup)
        {
            ENTITY::SET_ENTITY_AS_MISSION_ENTITY(ped, true, true);
            PED::DELETE_PED(&ped);
            return false;
        }
    }

    ENTITY::SET_ENTITY_AS_MISSION_ENTITY(ped, true, true);
    PED::SET_PED_RELATIONSHIP_GROUP_DEFAULT_HASH(ped, relationshipGroup);
    PED::SET_PED_RELATIONSHIP_GROUP_HASH(ped, relationshipGroup);
    if (voice && *voice)
        AUDIO::SET_AMBIENT_VOICE_NAME(ped, const_cast<char*>(voice));

    const DifficultyTuning& tuning = kDifficulty[static_cast<size_t>(difficultyIndex(slot.difficulty))];
    Fighter fighter{};
    fighter.ped = ped;
    fighter.model = model;
    fighter.group = relationshipGroup;
    fighter.team = teamIndex;
    fighter.spawnIndex = spawnIndex;
    fighter.originalSpawn = pos;
    fighter.originalHeading = heading;
    fighter.originalSpawnSet = true;
    fighter.pedSet = slot.pedSet;
    fighter.boss = slot.boss;
    fighter.special = slot.special;
    if (boss)
        fighter.outfitIndex = kBosses[static_cast<size_t>(slot.boss)].outfit;
    else if (specialPed)
        fighter.outfitIndex = specialPed->outfit;
    else if (namedPed)
        fighter.outfitIndex = namedPed->outfit;
    fighter.difficulty = slot.difficulty;
    fighter.voiceName = voice;
    fighter.baseName = leaderboardBaseNameForSpawn(slot, namedPed);
    fighter.displayName = nextFighterDisplayName(fighter.baseName, boss || special);
    fighter.maxHealth = tuning.health;
    fighter.lastHealth = tuning.health;
    fighter.hardened = tuning.hardened;
    fighter.heals = tuning.heals;
    if (boss)
    {
        fighter.maxHealth = kBosses[static_cast<size_t>(slot.boss)].health;
        fighter.lastHealth = fighter.maxHealth;
    }
    if (specialPed)
    {
        fighter.maxHealth = specialPed->health;
        fighter.lastHealth = specialPed->health;
        fighter.hardened = true;
        fighter.heals = false;
    }
    fighter.spawnedAt = now();
    fighter.lastDamage = fighter.spawnedAt;
    fighter.lastHeal = fighter.spawnedAt;
    seedFighterUpdateSchedule(fighter, fighter.spawnedAt);

    makePedVisible(ped);
    applyPedOutfit(ped, fighter.outfitIndex);
    applyPedTuning(fighter);
    fighter.combatWeapon = applyBattleWeapons(ped, slot, spawnIndex, &fighter.closeWeapon, &fighter.mediumWeapon, &fighter.longWeapon);
    resetWeaponController(fighter);
    resetScriptedActionState(fighter, true);
    resetIdleWatchdogState(fighter, fighter.spawnedAt, 0);
    fighter.lastWeaponSwitch = fighter.spawnedAt;
    ENTITY::SET_ENTITY_HEALTH(ped, fighter.maxHealth, 0);
    fighter.lastHealth = ENTITY::GET_ENTITY_HEALTH(ped);
    applyProtectedHeadshotMultiplierTest(fighter, "initial-spawn-final");
    applyExecutionThresholdProtection(fighter, fighter.lastHealth, false);
    if (battlePreparationActive())
    {
        ENTITY::FREEZE_ENTITY_POSITION(ped, true);
        AI::CLEAR_PED_TASKS(ped, true, false);
        AI::TASK_STAND_STILL(ped, 10000);
        fighter.lastTask = fighter.spawnedAt;
    }
    else
    {
        readyWeapon(fighter, now(), true);
        ensureFighterBlip(fighter);
    }

    g_runtime.fighters.push_back(fighter);
    return true;
}

void shuffleIntVector(std::vector<int>& values)
{
    for (int i = static_cast<int>(values.size()) - 1; i > 0; --i)
    {
        int swapIndex = randomRange(0, i);
        std::swap(values[static_cast<size_t>(i)], values[static_cast<size_t>(swapIndex)]);
    }
}

void arrangePlayerBattleRoyaleSquad()
{
    if (!g_runtime.freeForAll ||
        !g_runtime.playerParticipating ||
        g_runtime.freeForAllSpectate ||
        !g_runtime.playerFreeForAllGroup)
    {
        return;
    }

    int slot = 0;
    for (Fighter& fighter : g_runtime.fighters)
    {
        if (fighter.group != g_runtime.playerFreeForAllGroup || !exists(fighter.ped))
            continue;

        fighter.playerSquadSlot = slot++;
        moveFighterBesidePlayer(fighter);
        attachFighterToPlayerGroup(fighter);
    }
}

void arrangeNpcBattleRoyaleSquads()
{
    if (!g_runtime.freeForAll || g_runtime.freeForAllTeamSize <= 1)
        return;

    std::vector<Hash> arrangedGroups;
    arrangedGroups.reserve(g_runtime.fighters.size());

    for (Fighter& anchorFighter : g_runtime.fighters)
    {
        if (!exists(anchorFighter.ped) ||
            !anchorFighter.group ||
            (g_runtime.playerFreeForAllGroup && anchorFighter.group == g_runtime.playerFreeForAllGroup) ||
            std::find(arrangedGroups.begin(), arrangedGroups.end(), anchorFighter.group) != arrangedGroups.end())
        {
            continue;
        }

        arrangedGroups.push_back(anchorFighter.group);
        Vec3 anchor = entityCoords(anchorFighter.ped);
        float heading = headingToward(anchor, g_runtime.battleCenter) * (kPi / 180.0f);

        for (Fighter& fighter : g_runtime.fighters)
        {
            if (fighter.group != anchorFighter.group || !exists(fighter.ped))
                continue;

            moveFighterToSquadOffset(fighter, anchor, heading);
        }
    }
}

bool assignBattleRoyaleTeams()
{
    if (!g_runtime.freeForAll)
        return true;

    g_runtime.playerFreeForAllGroup = 0;
    g_runtime.freeForAllTeamSize = std::clamp(g_menu.battleRoyaleTeamSize, 1, 4);
    for (Fighter& fighter : g_runtime.fighters)
    {
        fighter.battleRoyaleSquad = -1;
        fighter.battleRoyaleSquadSlot = -1;
        fighter.playerSquadSlot = -1;
    }

    std::vector<int> combatants;
    combatants.reserve(g_runtime.fighters.size() + 1);
    if (g_runtime.playerParticipating)
        combatants.push_back(-1);

    for (int i = 0; i < static_cast<int>(g_runtime.fighters.size()); ++i)
        combatants.push_back(i);

    shuffleIntVector(combatants);

    for (int start = 0, squad = 0; start < static_cast<int>(combatants.size()); start += g_runtime.freeForAllTeamSize, ++squad)
    {
        Hash group = createFreeForAllRelationshipGroup(70000 + squad);
        if (!group)
            return false;
        int teamIndex = squad % kTeamCount;
        int end = std::min(start + g_runtime.freeForAllTeamSize, static_cast<int>(combatants.size()));
        for (int i = start; i < end; ++i)
        {
            int combatant = combatants[static_cast<size_t>(i)];
            if (combatant < 0)
            {
                g_runtime.playerFreeForAllGroup = group;
                g_runtime.playerTeam = teamIndex;
                continue;
            }

            Fighter& fighter = g_runtime.fighters[static_cast<size_t>(combatant)];
            if (fighter.group && fighter.group != group)
                setDamagePermission(fighter.ped, fighter.group, true);
            fighter.group = group;
            fighter.team = teamIndex;
            fighter.battleRoyaleSquad = squad;
            fighter.battleRoyaleSquadSlot = i - start;
            PED::SET_PED_RELATIONSHIP_GROUP_DEFAULT_HASH(fighter.ped, group);
            PED::SET_PED_RELATIONSHIP_GROUP_HASH(fighter.ped, group);
            resetDamagePermissionCache(fighter);
            seedFighterUpdateSchedule(fighter, now());
            markRelationshipsDirty();
            removeFighterBlip(fighter);
        }
    }

    removeFreeForAllRelationshipGroup(g_runtime.freeForAllSpawnGroup);
    debugFreeForAllGroupCounts();
    arrangeNpcBattleRoyaleSquads();
    arrangePlayerBattleRoyaleSquad();
    for (Fighter& fighter : g_runtime.fighters)
        applyDamagePermissions(fighter);
    markRelationshipsDirty();
    return true;
}

void failBattlePreparation(const std::string& message)
{
    g_runtime.preparationPhase = BattlePreparationPhase::Failed;
    deleteFighters();
    removeRelationshipGroups();
    setStatus(message, 9000);
}

PlayerRelation preparationRelationToPlayer(Hash group)
{
    if (g_runtime.freeForAllSpectate || g_runtime.playerSpectating || (g_runtime.playerEliminated && !g_runtime.deathmatch))
        return PlayerRelation::Neutral;
    if (g_runtime.playerFreeForAllGroup && group == g_runtime.playerFreeForAllGroup)
        return PlayerRelation::Friendly;
    return PlayerRelation::Hostile;
}

void setPreparationStatus(const char* label, int done, int total)
{
    char buffer[112]{};
    std::snprintf(buffer, sizeof(buffer), "%s: %d/%d", label, std::max(0, done), std::max(0, total));
    setStatus(buffer, 1500);
}

void beginFreeForAllGroupPreparation()
{
    g_runtime.playerFreeForAllGroup = 0;
    g_runtime.freeForAllTeamSize = std::clamp(g_menu.battleRoyaleTeamSize, 1, 4);
    g_runtime.preparationCombatants.clear();
    g_runtime.preparationGroups.clear();
    g_runtime.preparationCombatants.reserve(g_runtime.fighters.size() + 1);
    if (g_runtime.playerParticipating)
        g_runtime.preparationCombatants.push_back(-1);

    for (int i = 0; i < static_cast<int>(g_runtime.fighters.size()); ++i)
    {
        Fighter& fighter = g_runtime.fighters[static_cast<size_t>(i)];
        fighter.battleRoyaleSquad = -1;
        fighter.battleRoyaleSquadSlot = -1;
        fighter.playerSquadSlot = -1;
        g_runtime.preparationCombatants.push_back(i);
    }

    shuffleIntVector(g_runtime.preparationCombatants);
    int combatants = static_cast<int>(g_runtime.preparationCombatants.size());
    g_runtime.preparationExpectedGroups = (combatants + g_runtime.freeForAllTeamSize - 1) / g_runtime.freeForAllTeamSize;
    if (combatants < 2 || g_runtime.preparationExpectedGroups < 2)
    {
        failBattlePreparation("Not enough valid battle peds could be spawned");
        return;
    }

    g_runtime.preparationGroups.reserve(static_cast<size_t>(g_runtime.preparationExpectedGroups));
    g_runtime.preparationSquadIndex = 0;
    g_runtime.preparationPhase = BattlePreparationPhase::AssigningGroups;
    setPreparationStatus("Preparing groups", 0, g_runtime.preparationExpectedGroups);
}

void advancePreparationSpawning()
{
    int attemptsThisFrame = 0;
    while (attemptsThisFrame < kPreparationSpawnBatchSize &&
        g_runtime.preparationSetIndex < static_cast<int>(g_battleRoyaleSets.size()))
    {
        const TeamRosterSlot& slot = g_battleRoyaleSets[static_cast<size_t>(g_runtime.preparationSetIndex)];
        int count = effectiveSlotCount(slot);
        if (g_runtime.preparationSetMember >= count)
        {
            ++g_runtime.preparationSetIndex;
            g_runtime.preparationSetMember = 0;
            continue;
        }

        if (spawnFighterFromSlot(slot, g_runtime.preparationSetIndex % kTeamCount, g_runtime.preparationGlobalSpawnIndex))
            ++g_runtime.preparationSpawnedFighters;
        ++g_runtime.preparationGlobalSpawnIndex;
        ++g_runtime.preparationSetMember;
        ++attemptsThisFrame;
    }

    g_runtime.preparationMaxFightersPerFrame = std::max(g_runtime.preparationMaxFightersPerFrame, attemptsThisFrame);
    setPreparationStatus("Preparing battle", g_runtime.preparationGlobalSpawnIndex, g_runtime.preparationRequestedFighters);

    if (g_runtime.preparationSetIndex >= static_cast<int>(g_battleRoyaleSets.size()))
        beginFreeForAllGroupPreparation();
}

void advancePreparationGroupAssignment()
{
    int createdThisFrame = 0;
    int totalCombatants = static_cast<int>(g_runtime.preparationCombatants.size());
    while (createdThisFrame < kPreparationGroupCreatesPerFrame &&
        g_runtime.preparationSquadIndex < g_runtime.preparationExpectedGroups)
    {
        int squad = g_runtime.preparationSquadIndex;
        Hash group = createFreeForAllRelationshipGroup(70000 + squad);
        if (!group)
        {
            g_runtime.preparationGroupCreationFailed = true;
            failBattlePreparation("Engine relationship-group limit reached during group creation");
            return;
        }

        g_runtime.preparationGroups.push_back(group);
        int teamIndex = squad % kTeamCount;
        int start = squad * g_runtime.freeForAllTeamSize;
        int end = std::min(start + g_runtime.freeForAllTeamSize, totalCombatants);
        for (int i = start; i < end; ++i)
        {
            int combatant = g_runtime.preparationCombatants[static_cast<size_t>(i)];
            if (combatant < 0)
            {
                g_runtime.playerFreeForAllGroup = group;
                g_runtime.playerTeam = teamIndex;
                continue;
            }

            Fighter& fighter = g_runtime.fighters[static_cast<size_t>(combatant)];
            if (fighter.group && fighter.group != group)
                setDamagePermission(fighter.ped, fighter.group, true);
            fighter.group = group;
            fighter.team = teamIndex;
            fighter.battleRoyaleSquad = squad;
            fighter.battleRoyaleSquadSlot = i - start;
            PED::SET_PED_RELATIONSHIP_GROUP_DEFAULT_HASH(fighter.ped, group);
            PED::SET_PED_RELATIONSHIP_GROUP_HASH(fighter.ped, group);
            resetDamagePermissionCache(fighter);
            seedFighterUpdateSchedule(fighter, now());
            removeFighterBlip(fighter);
        }

        ++g_runtime.preparationSquadIndex;
        ++createdThisFrame;
    }

    g_runtime.preparationMaxGroupsPerFrame = std::max(g_runtime.preparationMaxGroupsPerFrame, createdThisFrame);
    setPreparationStatus("Preparing groups", g_runtime.preparationSquadIndex, g_runtime.preparationExpectedGroups);

    if (g_runtime.preparationSquadIndex < g_runtime.preparationExpectedGroups)
        return;

    removeFreeForAllRelationshipGroup(g_runtime.freeForAllSpawnGroup);
    debugFreeForAllGroupCounts();
    arrangeNpcBattleRoyaleSquads();
    arrangePlayerBattleRoyaleSquad();

    size_t groupCount = g_runtime.preparationGroups.size();
    g_runtime.preparationRelationshipPlayerIndex = 0;
    g_runtime.preparationRelationshipGroupA = 0;
    g_runtime.preparationRelationshipGroupB = groupCount > 1 ? 1 : 0;
    g_runtime.preparationRelationshipSettersDone = 0;
    g_runtime.preparationRelationshipSettersTotal =
        static_cast<int>(groupCount * 3 + groupCount * (groupCount > 0 ? groupCount - 1 : 0));
    g_runtime.relationshipsDirty = true;
    g_runtime.preparationPhase = BattlePreparationPhase::ApplyingRelationships;
    setPreparationStatus("Preparing relationships", 0, g_runtime.preparationRelationshipSettersTotal);
}

void advancePreparationRelationships()
{
    int budget = kPreparationRelationshipSetterBudget;
    int settersThisFrame = 0;
    Hash playerGroup = PED::GET_PED_RELATIONSHIP_GROUP_HASH(playerPed());
    size_t groupCount = g_runtime.preparationGroups.size();

    while (budget >= 3 && g_runtime.preparationRelationshipPlayerIndex < groupCount)
    {
        Hash group = g_runtime.preparationGroups[g_runtime.preparationRelationshipPlayerIndex];
        int relation = relationToPlayerValue(preparationRelationToPlayer(group));
        PED::SET_RELATIONSHIP_BETWEEN_GROUPS(relation, group, playerGroup);
        PED::SET_RELATIONSHIP_BETWEEN_GROUPS(relation, playerGroup, group);
        PED::SET_RELATIONSHIP_BETWEEN_GROUPS(0, group, group);
        budget -= 3;
        settersThisFrame += 3;
        g_runtime.preparationRelationshipSettersDone += 3;
        ++g_runtime.preparationRelationshipPlayerIndex;
    }

    while (budget >= 2 && g_runtime.preparationRelationshipGroupA < groupCount)
    {
        if (g_runtime.preparationRelationshipGroupB >= groupCount)
        {
            ++g_runtime.preparationRelationshipGroupA;
            g_runtime.preparationRelationshipGroupB = g_runtime.preparationRelationshipGroupA + 1;
            continue;
        }

        Hash a = g_runtime.preparationGroups[g_runtime.preparationRelationshipGroupA];
        Hash b = g_runtime.preparationGroups[g_runtime.preparationRelationshipGroupB];
        PED::SET_RELATIONSHIP_BETWEEN_GROUPS(5, a, b);
        PED::SET_RELATIONSHIP_BETWEEN_GROUPS(5, b, a);
        budget -= 2;
        settersThisFrame += 2;
        g_runtime.preparationRelationshipSettersDone += 2;
        ++g_runtime.preparationRelationshipGroupB;
    }

    g_runtime.preparationMaxRelationshipSettersPerFrame =
        std::max(g_runtime.preparationMaxRelationshipSettersPerFrame, settersThisFrame);
    setPreparationStatus(
        "Preparing relationships",
        g_runtime.preparationRelationshipSettersDone,
        g_runtime.preparationRelationshipSettersTotal);

    bool playerStageDone = g_runtime.preparationRelationshipPlayerIndex >= groupCount;
    bool pairStageDone = g_runtime.preparationRelationshipGroupA >= groupCount;
    if (!playerStageDone || !pairStageDone)
        return;

    g_runtime.relationshipsDirty = false;
    g_runtime.lastRelationshipSafetyRefresh = now();
    g_runtime.lastRelationshipValidation = now();
    g_runtime.preparationFighterIndex = 0;
    g_runtime.preparationPhase = BattlePreparationPhase::ApplyingDamagePermissions;
    setPreparationStatus("Preparing damage", 0, static_cast<int>(g_runtime.fighters.size()));
}

void advancePreparationDamagePermissions()
{
    int processed = 0;
    while (processed < kPreparationFightersPerFrame &&
        g_runtime.preparationFighterIndex < static_cast<int>(g_runtime.fighters.size()))
    {
        Fighter& fighter = g_runtime.fighters[static_cast<size_t>(g_runtime.preparationFighterIndex)];
        applyDamagePermissions(fighter);
        ++g_runtime.preparationFighterIndex;
        ++processed;
    }

    g_runtime.preparationMaxFightersPerFrame = std::max(g_runtime.preparationMaxFightersPerFrame, processed);
    setPreparationStatus("Preparing damage", g_runtime.preparationFighterIndex, static_cast<int>(g_runtime.fighters.size()));

    if (g_runtime.preparationFighterIndex < static_cast<int>(g_runtime.fighters.size()))
        return;

    g_runtime.preparationFighterIndex = 0;
    g_runtime.preparationPhase = BattlePreparationPhase::PreparingFighters;
    setPreparationStatus("Preparing fighters", 0, static_cast<int>(g_runtime.fighters.size()));
}

void beginPreparedFreeForAllActivation()
{
    g_runtime.battleActive = true;
    g_runtime.resultAnnounced = false;
    g_runtime.initialActiveTeams = g_runtime.preparationSpawnedFighters;
    g_runtime.playerWasParticipant = g_runtime.playerParticipating;
    resetPlayerDamageAttribution();
    setBattleRespawnOverride(true);
    if (g_settings.neverWantedDuringBattles)
        suppressWantedDuringBattle();

    DWORD t = now();
    g_runtime.startCountdownActive = g_settings.startCountdownSeconds > 0;
    g_runtime.startCountdownEndsAt = g_runtime.startCountdownActive ?
        t + static_cast<DWORD>(g_settings.startCountdownSeconds) * 1000u :
        0;
    g_runtime.relationshipsDirty = false;
    g_runtime.preparationFighterIndex = 0;
    g_runtime.preparationPhase = BattlePreparationPhase::StartingCombat;
}

void advancePreparationFighterSetup()
{
    DWORD t = now();
    int processed = 0;
    while (processed < kPreparationFightersPerFrame &&
        g_runtime.preparationFighterIndex < static_cast<int>(g_runtime.fighters.size()))
    {
        Fighter& fighter = g_runtime.fighters[static_cast<size_t>(g_runtime.preparationFighterIndex)];
        if (exists(fighter.ped))
        {
            repairDynamicPedTuning(fighter, t);
            readyWeapon(fighter, t, true);
            ensureFighterBlip(fighter);
        }
        ++g_runtime.preparationFighterIndex;
        ++processed;
    }

    g_runtime.preparationMaxFightersPerFrame = std::max(g_runtime.preparationMaxFightersPerFrame, processed);
    setPreparationStatus("Preparing fighters", g_runtime.preparationFighterIndex, static_cast<int>(g_runtime.fighters.size()));

    if (g_runtime.preparationFighterIndex < static_cast<int>(g_runtime.fighters.size()))
        return;

    beginPreparedFreeForAllActivation();
}

void finishBattlePreparation()
{
    char buffer[160]{};
    const char* modePrefix = g_runtime.deathmatch ? "Free For All " : "Battle Royale ";
    std::snprintf(
        buffer,
        sizeof(buffer),
        "Started %s%s battle with %d/%d fighters",
        modePrefix,
        battleTypeName(g_menu.battleType),
        g_runtime.preparationSpawnedFighters,
        g_runtime.preparationRequestedFighters);

    if (g_runtime.startCountdownActive)
    {
        DWORD t = now();
        g_runtime.startCountdownEndsAt = t + static_cast<DWORD>(g_settings.startCountdownSeconds) * 1000u;
        std::snprintf(buffer, sizeof(buffer), "Battle starts in %d", startCountdownRemainingSeconds());
    }

    g_runtime.preparationPhase = BattlePreparationPhase::None;
    g_runtime.preparationCombatants.clear();
    g_runtime.preparationGroups.clear();
    g_menu.open = false;
    setStatus(buffer, 7000);
    if (g_runtime.playerSpectating)
        cycleSpectatorCamera();
}

void advancePreparationCombatStart()
{
    DWORD t = now();
    int processed = 0;
    while (processed < kPreparationFightersPerFrame &&
        g_runtime.preparationFighterIndex < static_cast<int>(g_runtime.fighters.size()))
    {
        Fighter& fighter = g_runtime.fighters[static_cast<size_t>(g_runtime.preparationFighterIndex)];
        if (isAlive(fighter) && exists(fighter.ped))
        {
            AI::CLEAR_PED_TASKS(fighter.ped, true, false);
            fighter.lastTask = 0;
            fighter.lastRepositionTask = 0;
            fighter.lastShotTask = 0;
            fighter.currentTarget = 0;
            fighter.currentTargetStartedAt = 0;
            resetIdleWatchdogState(fighter, t, 0);
            seedFighterUpdateSchedule(fighter, t);
            if (g_runtime.startCountdownActive)
            {
                ENTITY::FREEZE_ENTITY_POSITION(fighter.ped, true);
                holdFighterForStartCountdown(fighter, t);
            }
            else
            {
                ENTITY::FREEZE_ENTITY_POSITION(fighter.ped, false);
                taskFighter(fighter, t, true);
            }
        }
        ++g_runtime.preparationFighterIndex;
        ++processed;
    }

    g_runtime.preparationMaxFightersPerFrame = std::max(g_runtime.preparationMaxFightersPerFrame, processed);
    setPreparationStatus("Preparing combat", g_runtime.preparationFighterIndex, static_cast<int>(g_runtime.fighters.size()));

    if (g_runtime.preparationFighterIndex >= static_cast<int>(g_runtime.fighters.size()))
        finishBattlePreparation();
}

void updateBattlePreparation()
{
    switch (g_runtime.preparationPhase)
    {
    case BattlePreparationPhase::SpawningFighters:
        advancePreparationSpawning();
        break;
    case BattlePreparationPhase::AssigningGroups:
        advancePreparationGroupAssignment();
        break;
    case BattlePreparationPhase::ApplyingRelationships:
        advancePreparationRelationships();
        break;
    case BattlePreparationPhase::ApplyingDamagePermissions:
        advancePreparationDamagePermissions();
        break;
    case BattlePreparationPhase::PreparingFighters:
        advancePreparationFighterSetup();
        break;
    case BattlePreparationPhase::StartingCombat:
        advancePreparationCombatStart();
        break;
    case BattlePreparationPhase::None:
    case BattlePreparationPhase::Failed:
    default:
        break;
    }
}

void startBattle()
{
    if (battlePreparationActive())
    {
        setStatus("Battle is still preparing", 3500);
        return;
    }

    clearLeaderboard();
    g_runtime.playerKills = 0;
    g_runtime.playerDeaths = 0;
    g_runtime.playerFinishPosition = 0;
    g_runtime.playerKillerPed = 0;
    g_runtime.playerKillerName.clear();
    g_runtime.playerKillerRecorded = false;
    g_runtime.playerVitalsRefillUntil = 0;
    stopBossDodgeDeadEyeSuppression();
    deleteFighters();
    g_runtime.neutralTeamProvokedByPlayer.fill(false);
    g_runtime.freeForAll = freeForAllSelected();
    g_runtime.deathmatch = deathmatchSelected();
    if (g_runtime.freeForAll)
        removeRelationshipGroups();
    g_runtime.playerSpectating = g_runtime.freeForAll && g_menu.freeForAllSpectate;
    g_runtime.freeForAllSpectate = g_runtime.freeForAll && g_menu.freeForAllSpectate;
    g_runtime.playerTeam = g_runtime.playerSpectating ? -1 : playerTeamForCurrentBattle();
    g_runtime.playerParticipating = g_runtime.playerSpectating ? false : (g_runtime.freeForAll ? !g_runtime.freeForAllSpectate : g_runtime.playerTeam >= 0);
    g_runtime.playerWasParticipant = false;
    g_runtime.playerEliminated = false;
    g_runtime.playerRevivePending = false;
    g_runtime.playerSafePosValid = false;
    g_runtime.playerScreenRepairUntil = 0;
    rememberPlayerSafePosition();
    g_runtime.battleCenter = entityCoords(playerPed());

    int requested = requestedFighterCount();
    int configuredTeams = activeConfiguredTeams();
    if (g_runtime.freeForAll)
    {
        int requiredFighters = g_runtime.playerParticipating ? 1 : 2;
        if (requested < requiredFighters)
        {
            bool playerWillFight = g_runtime.playerParticipating;
            g_runtime.playerParticipating = false;
            setStatus(playerWillFight ? "Add at least one fighter" : "Add at least two fighters to spectate", 7000);
            return;
        }
    }
    else if (configuredTeams < 2 && !anyHostileTeamConfigured())
    {
        g_runtime.playerParticipating = false;
        g_runtime.playerEliminated = false;
        g_runtime.playerTeam = -1;
        setStatus("Enable at least two teams, or one hostile team", 7000);
        return;
    }

    if (!g_runtime.freeForAll)
    {
        if (!createRelationshipGroups())
        {
            deleteFighters();
            removeRelationshipGroups();
            return;
        }
        markRelationshipsDirty();
    }

    g_runtime.fighters.reserve(static_cast<size_t>(requested));
    if (g_runtime.freeForAll)
    {
        int teamSize = std::max(1, std::clamp(g_menu.battleRoyaleTeamSize, 1, 4));
        int combatants = requested + (g_runtime.playerParticipating ? 1 : 0);
        int expectedGroups = (combatants + teamSize - 1) / teamSize;
        g_runtime.freeForAllGroups.reserve(static_cast<size_t>(expectedGroups + 1));
    }

    g_runtime.freeForAllSpawnAngle = static_cast<float>(randomRange(0, 359)) * (kPi / 180.0f);
    g_runtime.freeForAllPlayerScatterIndex = (g_runtime.freeForAll && g_runtime.playerParticipating) ?
        randomRange(0, requested) :
        -1;
    if (g_runtime.freeForAll)
    {
        g_runtime.freeForAllSpawnGroup = createFreeForAllRelationshipGroup(99998);
        if (!g_runtime.freeForAllSpawnGroup)
        {
            deleteFighters();
            removeRelationshipGroups();
            setStatus("Could not create battle relationship group", 7000);
            return;
        }
        Hash playerGroup = PED::GET_PED_RELATIONSHIP_GROUP_HASH(playerPed());
        PED::SET_RELATIONSHIP_BETWEEN_GROUPS(3, g_runtime.freeForAllSpawnGroup, playerGroup);
        PED::SET_RELATIONSHIP_BETWEEN_GROUPS(3, playerGroup, g_runtime.freeForAllSpawnGroup);
        PED::SET_RELATIONSHIP_BETWEEN_GROUPS(0, g_runtime.freeForAllSpawnGroup, g_runtime.freeForAllSpawnGroup);
    }

    if (g_runtime.freeForAll)
    {
        g_runtime.preparationPhase = BattlePreparationPhase::SpawningFighters;
        g_runtime.preparationRequestedFighters = requested;
        g_runtime.preparationSpawnedFighters = 0;
        g_runtime.preparationExpectedGroups = 0;
        g_runtime.preparationSetIndex = 0;
        g_runtime.preparationSetMember = 0;
        g_runtime.preparationGlobalSpawnIndex = 0;
        g_runtime.preparationSquadIndex = 0;
        g_runtime.preparationFighterIndex = 0;
        g_runtime.preparationRelationshipPlayerIndex = 0;
        g_runtime.preparationRelationshipGroupA = 0;
        g_runtime.preparationRelationshipGroupB = 1;
        g_runtime.preparationRelationshipSettersDone = 0;
        g_runtime.preparationRelationshipSettersTotal = 0;
        g_runtime.preparationMaxGroupsPerFrame = 0;
        g_runtime.preparationMaxRelationshipSettersPerFrame = 0;
        g_runtime.preparationMaxFightersPerFrame = 0;
        g_runtime.preparationGroupCreationFailed = false;
        g_runtime.preparationCombatants.clear();
        g_runtime.preparationGroups.clear();
        g_runtime.relationshipsDirty = true;
        setPreparationStatus("Preparing battle", 0, requested);
        g_menu.open = false;
        return;
    }

    int spawned = 0;
    int globalSpawnIndex = 0;
    auto yieldSpawnBatch = [&](int attempted) {
        if (attempted > 0 && attempted % kSpawnYieldBatchSize == 0)
        {
            char preparing[96]{};
            std::snprintf(preparing, sizeof(preparing), "Preparing battle: %d/%d", std::min(attempted, requested), requested);
            setStatus(preparing, 2500);
            WAIT(0);
        }
    };
    if (!g_runtime.freeForAll)
    {
        for (int team = 0; team < kTeamCount; ++team)
        {
            int spawnIndex = 0;
            for (const TeamRosterSlot& slot : g_teams[static_cast<size_t>(team)].sets)
            {
                int count = effectiveSlotCount(slot);
                for (int member = 0; member < count; ++member)
                {
                    if (spawnFighterFromSlot(slot, team, spawnIndex))
                        ++spawned;
                    ++spawnIndex;
                    yieldSpawnBatch(spawned);
                }
            }
        }
    }

    int activeSpawnedTeams = spawnedTeamCount();
    bool notEnoughSpawned = g_runtime.freeForAll ?
        (spawned + (g_runtime.playerParticipating ? 1 : 0) < 2 || aliveBattleRoyaleGroupCount() < 2) :
        (spawned == 0 || (activeSpawnedTeams < 2 && !spawnedHostileTeamExists()));
    if (notEnoughSpawned)
    {
        deleteFighters();
        removeRelationshipGroups();
        setStatus("Not enough valid battle peds could be spawned", 7000);
        return;
    }

    g_runtime.battleActive = true;
    g_runtime.resultAnnounced = false;
    g_runtime.initialActiveTeams = g_runtime.freeForAll ? spawned : activeSpawnedTeams;
    g_runtime.playerWasParticipant = g_runtime.playerParticipating;
    resetPlayerDamageAttribution();
    setBattleRespawnOverride(true);
    if (g_settings.neverWantedDuringBattles)
        suppressWantedDuringBattle();
    DWORD t = now();
    g_runtime.startCountdownActive = g_settings.startCountdownSeconds > 0;
    g_runtime.startCountdownEndsAt = g_runtime.startCountdownActive ?
        t + static_cast<DWORD>(g_settings.startCountdownSeconds) * 1000u :
        0;
    markRelationshipsDirty();
    updateRelationshipsIfNeeded(t);
    for (Fighter& fighter : g_runtime.fighters)
    {
        if (exists(fighter.ped))
            AI::CLEAR_PED_TASKS(fighter.ped, true, false);
        repairDynamicPedTuning(fighter, t);
        readyWeapon(fighter, t, true);
        if (g_runtime.startCountdownActive)
            holdFighterForStartCountdown(fighter, t);
        else
            taskFighter(fighter, t, true);
    }

    char buffer[128]{};
    const char* modePrefix = g_runtime.freeForAll ?
        (g_runtime.deathmatch ? "Free For All " : "Battle Royale ") :
        (g_runtime.deathmatch ? "Team Deathmatch " : "");
    if (spawned == requested)
        std::snprintf(
            buffer,
            sizeof(buffer),
            "Started %s%s battle with %d fighters",
            modePrefix,
            battleTypeName(g_menu.battleType),
            spawned);
    else
        std::snprintf(
            buffer,
            sizeof(buffer),
            "Started %s%s battle with %d/%d fighters",
            modePrefix,
            battleTypeName(g_menu.battleType),
            spawned,
            requested);
    if (g_runtime.startCountdownActive)
    {
        std::snprintf(buffer, sizeof(buffer), "Battle starts in %d", startCountdownRemainingSeconds());
        setStatus(buffer, 7000);
    }
    else
    {
        setStatus(buffer, 7000);
    }
    g_menu.open = false;
    if (g_runtime.playerSpectating)
        cycleSpectatorCamera();
}

void drawTextLine(const std::string& text, float x, float y, float scale, int r, int g, int b, int a, bool centered = false)
{
    UI::SET_TEXT_SCALE(0.0f, scale);
    UI::SET_TEXT_COLOR_RGBA(r, g, b, a);
    UI::SET_TEXT_CENTRE(centered);
    UI::SET_TEXT_DROPSHADOW(1, 0, 0, 0, 210);
    UI::DRAW_TEXT(GAMEPLAY::CREATE_STRING(10, const_cast<char*>("LITERAL_STRING"), const_cast<char*>(text.c_str())), x, y);
}

std::string selectedPrefix(int row)
{
    return g_menu.row == row ? "> " : "  ";
}

void drawSettingsMenu()
{
    GRAPHICS::DRAW_RECT(0.45f, 0.47f, 0.76f, 0.72f, 8, 10, 12, 205, true, true);
    GRAPHICS::DRAW_RECT(0.45f, 0.151f, 0.76f, 0.058f, 120, 32, 32, 230, true, true);

    drawTextLine("BATTLE CREATOR SETTINGS", 0.075f, 0.126f, 0.42f, 245, 236, 218, 255);
    drawTextLine("F9 close | Left/Right edit | Enter select | R reload INI | Shift bigger steps", 0.075f, 0.174f, 0.245f, 210, 205, 190, 235);

    std::vector<std::string> rows;
    rows.reserve(kSettingsMenuRows);
    rows.push_back(selectedPrefix(0) + std::string("Back to battle setup"));
    rows.push_back(selectedPrefix(1) + toggleSettingText("Auto-spectate on death", g_settings.forcePlayerSpectator));
    rows.push_back(selectedPrefix(2) + toggleSettingText("Manual team spawns", g_settings.enableManualTeamSpawns));
    rows.push_back(selectedPrefix(3) + toggleSettingText("Neutrals friendly until hit", g_settings.neutralsFriendlyUntilAttacked));
    rows.push_back(selectedPrefix(4) + toggleSettingText("No Dead Eye", g_settings.noDeadEyeDuringBattles));
    rows.push_back(selectedPrefix(5) + secondsSettingText("Start countdown", g_settings.startCountdownSeconds));
    rows.push_back(selectedPrefix(6) + distanceLimitSettingText("Spectate range", g_settings.spectatorMaxTargetDistance));
    rows.push_back(selectedPrefix(7) + floatSettingText("All Weapons distance", g_settings.firearmSpawnDistance));
    rows.push_back(selectedPrefix(8) + floatSettingText("Melee distance", g_settings.meleeSpawnDistance));
    rows.push_back(selectedPrefix(9) + floatSettingText("No Weapons distance", g_settings.unarmedSpawnDistance));
    rows.push_back(selectedPrefix(10) + intSettingText("Max team count", g_settings.maxTeamCount));
    rows.push_back(selectedPrefix(11) + std::string("Default score limit: ") + (g_settings.defaultDeathmatchKillLimit <= 0 ? "Endless" : std::to_string(g_settings.defaultDeathmatchKillLimit)));
    rows.push_back(selectedPrefix(12) + dwordSettingText("NPC respawn delay", g_settings.npcDeathmatchRespawnDelayMs));
    rows.push_back(selectedPrefix(13) + toggleSettingText("TDM original respawns", g_settings.respawnTeamDeathmatchAtOriginalSpawn));
    rows.push_back(selectedPrefix(14) + std::string("Preset slot: ") + std::to_string(g_menu.presetSlot));
    rows.push_back(selectedPrefix(15) + std::string("Save battle preset"));
    rows.push_back(selectedPrefix(16) + std::string("Load battle preset"));
    rows.push_back(selectedPrefix(17) + std::string("Save settings"));
    rows.push_back(selectedPrefix(18) + std::string("Reload settings from INI"));

    float y = 0.212f;
    float rowStep = rows.size() > 20 ? 0.0265f : (rows.size() > 17 ? 0.0285f : (rows.size() > 14 ? 0.031f : 0.038f));
    float normalScale = rows.size() > 20 ? 0.228f : (rows.size() > 17 ? 0.242f : 0.275f);
    float selectedScale = rows.size() > 20 ? 0.252f : (rows.size() > 17 ? 0.265f : 0.300f);
    for (int i = 0; i < static_cast<int>(rows.size()); ++i)
    {
        bool selected = g_menu.row == i;
        drawTextLine(rows[static_cast<size_t>(i)], 0.075f, y, selected ? selectedScale : normalScale, selected ? 255 : 225, selected ? 236 : 220, selected ? 178 : 205, 255);
        y += rowStep;
    }

    std::string status = g_runtime.status.empty() ? "Ready" : g_runtime.status;
    drawTextLine(status, 0.075f, 0.796f, 0.245f, 220, 235, 220, 245);
}

int menuRowCount()
{
    if (g_menu.settingsPage)
        return kSettingsMenuRows;

    int rows = 0;
    int maxRows = maxLogicalMenuRows();
    for (int logical = 0; logical < maxRows; ++logical)
    {
        if (menuLogicalRowVisible(logical))
            ++rows;
    }
    return rows;
}

int startBattleMenuRow()
{
    return visibleMenuRow(freeForAllSelected() ? 14 : 16);
}

int clearBattleMenuRow()
{
    return visibleMenuRow(freeForAllSelected() ? 15 : 17);
}

std::string countText(const TeamRosterSlot& slot)
{
    if (slot.count <= 0)
        return "Disabled";
    char buffer[32]{};
    std::snprintf(buffer, sizeof(buffer), "%d", effectiveSlotCount(slot));
    return buffer;
}

const char* unitName(const TeamRosterSlot& slot)
{
    if (slot.difficulty == Difficulty::Bosses)
        return kBosses[static_cast<size_t>(slot.boss)].name;
    if (slot.difficulty == Difficulty::Special)
        return kSpecialPeds[static_cast<size_t>(slot.special)].name;
    return g_pedSets[static_cast<size_t>(slot.pedSet)].name;
}

std::string teamSetSummary(int teamIndex, int setIndex)
{
    if (teamIndex < 0 || teamIndex >= kTeamCount)
        return "No team selected";

    const std::vector<TeamRosterSlot>& sets = g_teams[static_cast<size_t>(teamIndex)].sets;
    if (setIndex < 0 || setIndex >= static_cast<int>(sets.size()))
        return "No set selected";

    const TeamRosterSlot& slot = sets[static_cast<size_t>(setIndex)];
    char buffer[160]{};
    if (effectiveSlotCount(slot) <= 0)
    {
        std::snprintf(buffer, sizeof(buffer), "Set %d: Disabled", setIndex + 1);
        return buffer;
    }

    std::snprintf(
        buffer,
        sizeof(buffer),
        "%d. %dx %s, %s",
        setIndex + 1,
        effectiveSlotCount(slot),
        unitName(slot),
        difficultyName(slot.difficulty));
    return buffer;
}

std::string battleRoyaleSetSummary(int index)
{
    if (index < 0 || index >= static_cast<int>(g_battleRoyaleSets.size()))
        return "No set selected";

    const TeamRosterSlot& slot = g_battleRoyaleSets[static_cast<size_t>(index)];
    char buffer[160]{};
    std::snprintf(
        buffer,
        sizeof(buffer),
        "%d. %dx %s, %s",
        index + 1,
        effectiveSlotCount(slot),
        unitName(slot),
        difficultyName(slot.difficulty));
    return buffer;
}

std::string battleRoyaleDraftSummary()
{
    const TeamRosterSlot& slot = g_menu.battleRoyaleDraft;
    char buffer[160]{};
    std::snprintf(
        buffer,
        sizeof(buffer),
        "Editor: %dx %s, %s",
        effectiveSlotCount(slot),
        unitName(slot),
        difficultyName(slot.difficulty));
    return buffer;
}

std::string teamSummary(int index)
{
    const TeamSetup& team = g_teams[static_cast<size_t>(index)];
    const char* label = "Team";

    if (!teamEnabled(team))
    {
        char buffer[96]{};
        std::snprintf(
            buffer,
            sizeof(buffer),
            "%s %d: Disabled%s",
            label,
            index + 1,
            (g_settings.enableManualTeamSpawns && team.manualSpawnSet) ? " [spawn set]" : "");
        return buffer;
    }

    std::string summary = std::string(label) + " " + std::to_string(index + 1) + ": ";
    int shown = 0;
    for (const TeamRosterSlot& slot : team.sets)
    {
        if (effectiveSlotCount(slot) <= 0)
            continue;

        if (shown > 0)
            summary += " + ";
        summary += std::to_string(effectiveSlotCount(slot));
        summary += "x ";
        summary += unitName(slot);
        ++shown;
        if (shown >= 2)
            break;
    }

    int activeSlots = 0;
    for (const TeamRosterSlot& slot : team.sets)
    {
        if (effectiveSlotCount(slot) > 0)
            ++activeSlots;
    }

    if (activeSlots > shown)
        summary += " + more";

    summary += " (";
    summary += relationName(team.playerRelation);
    summary += ")";
    if (g_settings.enableManualTeamSpawns && team.manualSpawnSet)
        summary += " [spawn set]";
    return summary;
}

void clampRosterSlot(TeamRosterSlot& slot)
{
    slot.pedSet = std::clamp(slot.pedSet, 0, static_cast<int>(g_pedSets.size()) - 1);
    slot.boss = std::clamp(slot.boss, 0, static_cast<int>(kBosses.size()) - 1);
    slot.special = std::clamp(slot.special, 0, static_cast<int>(kSpecialPeds.size()) - 1);
    slot.count = std::clamp(slot.count, 0, maxCountForSlot(slot));
}

void clampAllRosterSlots()
{
    for (TeamSetup& team : g_teams)
    {
        for (TeamRosterSlot& slot : team.sets)
            clampRosterSlot(slot);
    }

    for (TeamRosterSlot& slot : g_battleRoyaleSets)
        clampRosterSlot(slot);

    clampRosterSlot(g_menu.battleRoyaleDraft);
}

void adjustSettingsSelected(int direction)
{
    bool shift = (GetAsyncKeyState(VK_SHIFT) & 0x8000) != 0;
    switch (g_menu.row)
    {
    case 1:
        g_settings.forcePlayerSpectator = !g_settings.forcePlayerSpectator;
        break;
    case 2:
        g_settings.enableManualTeamSpawns = !g_settings.enableManualTeamSpawns;
        clampCurrentSelection();
        break;
    case 3:
        g_settings.neutralsFriendlyUntilAttacked = !g_settings.neutralsFriendlyUntilAttacked;
        break;
    case 4:
        g_settings.noDeadEyeDuringBattles = !g_settings.noDeadEyeDuringBattles;
        break;
    case 5:
        g_settings.startCountdownSeconds = std::clamp(g_settings.startCountdownSeconds + direction * (shift ? 5 : 1), 0, 30);
        break;
    case 6:
    {
        float step = shift ? 25.0f : 10.0f;
        g_settings.spectatorMaxTargetDistance = std::clamp(
            g_settings.spectatorMaxTargetDistance + direction * step,
            0.0f,
            500.0f);
        if (g_settings.spectatorMaxTargetDistance < 5.0f)
            g_settings.spectatorMaxTargetDistance = 0.0f;
        break;
    }
    case 7:
        g_settings.firearmSpawnDistance = std::clamp(g_settings.firearmSpawnDistance + direction * (shift ? 5.0f : 1.0f), 2.0f, kMaxBattleSpawnDistance);
        break;
    case 8:
        g_settings.meleeSpawnDistance = std::clamp(g_settings.meleeSpawnDistance + direction * (shift ? 5.0f : 1.0f), 2.0f, kMaxBattleSpawnDistance);
        break;
    case 9:
        g_settings.unarmedSpawnDistance = std::clamp(g_settings.unarmedSpawnDistance + direction * (shift ? 5.0f : 1.0f), 2.0f, kMaxBattleSpawnDistance);
        break;
    case 10:
        g_settings.maxTeamCount = std::clamp(g_settings.maxTeamCount + direction * (shift ? 5 : 1), 1, 40);
        clampAllRosterSlots();
        break;
    case 11:
        g_settings.defaultDeathmatchKillLimit = clampDeathmatchKillLimitValue(g_settings.defaultDeathmatchKillLimit + direction * (shift ? 10 : 1));
        g_menu.killLimit = clampDeathmatchKillLimitValue(g_menu.killLimit);
        break;
    case 12:
        g_settings.npcDeathmatchRespawnDelayMs = static_cast<DWORD>(std::clamp(
            static_cast<int>(g_settings.npcDeathmatchRespawnDelayMs) + direction * (shift ? 1000 : 250),
            250,
            120000));
        break;
    case 13:
        g_settings.respawnTeamDeathmatchAtOriginalSpawn = !g_settings.respawnTeamDeathmatchAtOriginalSpawn;
        break;
    case 14:
        g_menu.presetSlot += direction;
        if (g_menu.presetSlot > kPresetSlotCount)
            g_menu.presetSlot = 1;
        else if (g_menu.presetSlot < 1)
            g_menu.presetSlot = kPresetSlotCount;
        break;
    default:
        break;
    }
}

bool loadSelectedBattleRoyaleSetIntoDraft(bool showStatus)
{
    if (g_battleRoyaleSets.empty())
    {
        if (showStatus)
            setStatus("No Battle Royale set selected", 4500);
        return false;
    }

    int index = std::clamp(g_menu.battleRoyaleSet, 0, static_cast<int>(g_battleRoyaleSets.size()) - 1);
    g_menu.battleRoyaleSet = index;
    g_menu.battleRoyaleDraft = g_battleRoyaleSets[static_cast<size_t>(index)];
    clampRosterSlot(g_menu.battleRoyaleDraft);
    if (showStatus)
        setStatus("Loaded selected set into editor", 4500);
    return true;
}

bool loadSelectedTeamSetIntoDraft(bool showStatus)
{
    TeamSetup& team = g_teams[static_cast<size_t>(g_menu.team)];
    if (team.sets.empty())
    {
        if (showStatus)
            setStatus("No team set selected", 4500);
        return false;
    }

    int index = std::clamp(g_menu.slot, 0, static_cast<int>(team.sets.size()) - 1);
    g_menu.slot = index;
    g_menu.battleRoyaleDraft = team.sets[static_cast<size_t>(index)];
    clampRosterSlot(g_menu.battleRoyaleDraft);
    if (showStatus)
        setStatus("Loaded selected team set into editor", 4500);
    return true;
}

void setRosterSlot(int teamIndex, int slotIndex, int count, int pedSet, Difficulty difficulty, int boss = 0, int special = 0)
{
    TeamSetup& team = g_teams[static_cast<size_t>(teamIndex)];
    if (slotIndex >= static_cast<int>(team.sets.size()))
        team.sets.resize(static_cast<size_t>(slotIndex + 1));
    TeamRosterSlot& slot = team.sets[static_cast<size_t>(slotIndex)];
    slot.count = count;
    slot.pedSet = std::clamp(pedSet, 0, static_cast<int>(g_pedSets.size()) - 1);
    slot.boss = std::clamp(boss, 0, static_cast<int>(kBosses.size()) - 1);
    slot.special = std::clamp(special, 0, static_cast<int>(kSpecialPeds.size()) - 1);
    slot.difficulty = difficulty;
    clampRosterSlot(slot);
}

void clearRosterSlots(int teamIndex)
{
    g_teams[static_cast<size_t>(teamIndex)].sets.clear();
}

void clearAllTeamRosters()
{
    for (int i = 0; i < kTeamCount; ++i)
        clearRosterSlots(i);
}

void setTeam(int index, PlayerRelation relation)
{
    clearRosterSlots(index);
    g_teams[static_cast<size_t>(index)].playerRelation = relation;
}

void setTeam(int index, int count, int pedSet, Difficulty difficulty, PlayerRelation relation, int boss = 0)
{
    setTeam(index, relation);
    if (count > 0)
        setRosterSlot(index, 0, count, pedSet, difficulty, boss);
}

void addTeamSet()
{
    clampRosterSlot(g_menu.battleRoyaleDraft);
    if (effectiveSlotCount(g_menu.battleRoyaleDraft) <= 0)
    {
        setStatus("Set count must be above 0", 4500);
        return;
    }

    TeamSetup& team = g_teams[static_cast<size_t>(g_menu.team)];
    team.sets.push_back(g_menu.battleRoyaleDraft);
    g_menu.slot = static_cast<int>(team.sets.size()) - 1;
    setStatus("Added set to Team " + std::to_string(g_menu.team + 1), 4500);
}

void removeSelectedTeamSet()
{
    TeamSetup& team = g_teams[static_cast<size_t>(g_menu.team)];
    if (team.sets.empty())
    {
        setStatus("No team sets to remove", 4500);
        return;
    }

    int index = std::clamp(g_menu.slot, 0, static_cast<int>(team.sets.size()) - 1);
    team.sets.erase(team.sets.begin() + index);
    if (team.sets.empty())
        g_menu.slot = 0;
    else
    {
        g_menu.slot = std::min(index, static_cast<int>(team.sets.size()) - 1);
        loadSelectedTeamSetIntoDraft(false);
    }
    setStatus("Removed set from Team " + std::to_string(g_menu.team + 1), 4500);
}

void updateSelectedTeamSet()
{
    TeamSetup& team = g_teams[static_cast<size_t>(g_menu.team)];
    if (team.sets.empty())
    {
        setStatus("No team set selected", 4500);
        return;
    }

    clampRosterSlot(g_menu.battleRoyaleDraft);
    if (effectiveSlotCount(g_menu.battleRoyaleDraft) <= 0)
    {
        setStatus("Set count must be above 0", 4500);
        return;
    }

    int index = std::clamp(g_menu.slot, 0, static_cast<int>(team.sets.size()) - 1);
    team.sets[static_cast<size_t>(index)] = g_menu.battleRoyaleDraft;
    setStatus("Updated Team " + std::to_string(g_menu.team + 1) + " set", 4500);
}

void clearSelectedTeamSets()
{
    clearRosterSlots(g_menu.team);
    g_menu.slot = 0;
    setStatus("Cleared Team " + std::to_string(g_menu.team + 1) + " sets", 4500);
}

void setManualSpawnForSelectedTeam()
{
    if (g_runtime.battleActive || battlePreparationActive())
    {
        setStatus("Cannot set team spawn during an active battle", 4500);
        return;
    }

    int teamIndex = std::clamp(g_menu.team, 0, kTeamCount - 1);
    TeamSetup& team = g_teams[static_cast<size_t>(teamIndex)];
    Vec3 pos = entityCoords(playerPed());
    team.manualSpawn = pos;
    team.manualSpawnSet = true;
    setStatus("Set spawn for Team " + std::to_string(teamIndex + 1), 4500);
}

void clearManualSpawnForSelectedTeam()
{
    int teamIndex = std::clamp(g_menu.team, 0, kTeamCount - 1);
    TeamSetup& team = g_teams[static_cast<size_t>(teamIndex)];
    if (!team.manualSpawnSet)
    {
        setStatus("Team " + std::to_string(teamIndex + 1) + " has no manual spawn", 4500);
        return;
    }

    team.manualSpawnSet = false;
    team.manualSpawn = Vec3{};
    setStatus("Cleared spawn for Team " + std::to_string(teamIndex + 1), 4500);
}

void clearAllManualTeamSpawns()
{
    for (TeamSetup& team : g_teams)
    {
        team.manualSpawnSet = false;
        team.manualSpawn = Vec3{};
    }
}

void addBattleRoyaleSet()
{
    clampRosterSlot(g_menu.battleRoyaleDraft);
    if (effectiveSlotCount(g_menu.battleRoyaleDraft) <= 0)
    {
        setStatus("Set count must be above 0", 4500);
        return;
    }

    g_battleRoyaleSets.push_back(g_menu.battleRoyaleDraft);
    g_menu.battleRoyaleSet = static_cast<int>(g_battleRoyaleSets.size()) - 1;
    setStatus("Added Battle Royale set", 4500);
}

void removeSelectedBattleRoyaleSet()
{
    if (g_battleRoyaleSets.empty())
    {
        setStatus("No Battle Royale sets to remove", 4500);
        return;
    }

    int index = std::clamp(g_menu.battleRoyaleSet, 0, static_cast<int>(g_battleRoyaleSets.size()) - 1);
    g_battleRoyaleSets.erase(g_battleRoyaleSets.begin() + index);
    if (g_battleRoyaleSets.empty())
        g_menu.battleRoyaleSet = 0;
    else
    {
        g_menu.battleRoyaleSet = std::min(index, static_cast<int>(g_battleRoyaleSets.size()) - 1);
        loadSelectedBattleRoyaleSetIntoDraft(false);
    }
    setStatus("Removed Battle Royale set", 4500);
}

void updateSelectedBattleRoyaleSet()
{
    if (g_battleRoyaleSets.empty())
    {
        setStatus("No Battle Royale set selected", 4500);
        return;
    }

    clampRosterSlot(g_menu.battleRoyaleDraft);
    if (effectiveSlotCount(g_menu.battleRoyaleDraft) <= 0)
    {
        setStatus("Set count must be above 0", 4500);
        return;
    }

    int index = std::clamp(g_menu.battleRoyaleSet, 0, static_cast<int>(g_battleRoyaleSets.size()) - 1);
    g_battleRoyaleSets[static_cast<size_t>(index)] = g_menu.battleRoyaleDraft;
    setStatus("Updated selected Battle Royale set", 4500);
}

void clearBattleRoyaleSets()
{
    g_battleRoyaleSets.clear();
    g_menu.battleRoyaleSet = 0;
    setStatus("Cleared Battle Royale sets", 4500);
}

std::string presetSectionName()
{
    int slot = std::clamp(g_menu.presetSlot, 1, kPresetSlotCount);
    return "Preset" + std::to_string(slot);
}

std::string presetKey(const std::string& prefix, const char* field)
{
    return prefix + field;
}

void writePresetRosterSlot(const std::string& section, const std::string& prefix, const TeamRosterSlot& slot)
{
    writePresetInt(section.c_str(), presetKey(prefix, "Count").c_str(), slot.count);
    writePresetInt(section.c_str(), presetKey(prefix, "PedSet").c_str(), slot.pedSet);
    writePresetInt(section.c_str(), presetKey(prefix, "Difficulty").c_str(), static_cast<int>(slot.difficulty));
    writePresetInt(section.c_str(), presetKey(prefix, "Boss").c_str(), slot.boss);
    writePresetInt(section.c_str(), presetKey(prefix, "Special").c_str(), slot.special);
}

TeamRosterSlot readPresetRosterSlot(const std::string& section, const std::string& prefix)
{
    TeamRosterSlot slot{};
    slot.count = readPresetInt(section.c_str(), presetKey(prefix, "Count").c_str(), 0);
    slot.pedSet = readPresetInt(section.c_str(), presetKey(prefix, "PedSet").c_str(), 0);
    int difficulty = readPresetInt(section.c_str(), presetKey(prefix, "Difficulty").c_str(), 0);
    difficulty = std::clamp(difficulty, 0, static_cast<int>(kDifficulty.size()) - 1);
    slot.difficulty = static_cast<Difficulty>(difficulty);
    slot.boss = readPresetInt(section.c_str(), presetKey(prefix, "Boss").c_str(), 0);
    slot.special = readPresetInt(section.c_str(), presetKey(prefix, "Special").c_str(), 0);
    clampRosterSlot(slot);
    return slot;
}

void saveCurrentBattlePreset()
{
    std::string section = presetSectionName();
    writePresetInt(section.c_str(), "Saved", 1);
    writePresetInt(section.c_str(), "Mode", static_cast<int>(g_menu.mode));
    writePresetInt(section.c_str(), "BattleType", static_cast<int>(g_menu.battleType));
    writePresetInt(section.c_str(), "KillLimit", g_menu.killLimit);
    writePresetInt(section.c_str(), "FreeForAllSpectate", g_menu.freeForAllSpectate ? 1 : 0);
    writePresetInt(section.c_str(), "BattleRoyaleTeamSize", g_menu.battleRoyaleTeamSize);

    for (int teamIndex = 0; teamIndex < kTeamCount; ++teamIndex)
    {
        const TeamSetup& team = g_teams[static_cast<size_t>(teamIndex)];
        std::string teamPrefix = "Team" + std::to_string(teamIndex);
        writePresetInt(section.c_str(), presetKey(teamPrefix, "Relation").c_str(), static_cast<int>(team.playerRelation));
        writePresetInt(section.c_str(), presetKey(teamPrefix, "ManualSpawnSet").c_str(), team.manualSpawnSet ? 1 : 0);
        writePresetFloat(section.c_str(), presetKey(teamPrefix, "ManualSpawnX").c_str(), team.manualSpawn.x);
        writePresetFloat(section.c_str(), presetKey(teamPrefix, "ManualSpawnY").c_str(), team.manualSpawn.y);
        writePresetFloat(section.c_str(), presetKey(teamPrefix, "ManualSpawnZ").c_str(), team.manualSpawn.z);
        int teamSetCount = std::min(static_cast<int>(team.sets.size()), 64);
        writePresetInt(section.c_str(), presetKey(teamPrefix, "SetCount").c_str(), teamSetCount);
        for (int setIndex = 0; setIndex < teamSetCount; ++setIndex)
        {
            writePresetRosterSlot(
                section,
                teamPrefix + "Set" + std::to_string(setIndex),
                team.sets[static_cast<size_t>(setIndex)]);
        }

        for (int slotIndex = 0; slotIndex < kRosterSlotCount; ++slotIndex)
        {
            TeamRosterSlot legacySlot{};
            if (slotIndex < teamSetCount)
                legacySlot = team.sets[static_cast<size_t>(slotIndex)];
            writePresetRosterSlot(section, teamPrefix + "Slot" + std::to_string(slotIndex), legacySlot);
        }
    }

    int setCount = std::min(static_cast<int>(g_battleRoyaleSets.size()), 64);
    writePresetInt(section.c_str(), "BattleRoyaleSetCount", setCount);
    for (int i = 0; i < setCount; ++i)
        writePresetRosterSlot(section, "BattleRoyaleSet" + std::to_string(i), g_battleRoyaleSets[static_cast<size_t>(i)]);
    writePresetRosterSlot(section, "Draft", g_menu.battleRoyaleDraft);

    flushBattleCreatorPresetsIni();
    setStatus("Saved battle preset slot " + std::to_string(g_menu.presetSlot), 5000);
}

void loadCurrentBattlePreset()
{
    std::string section = presetSectionName();
    if (readPresetInt(section.c_str(), "Saved", 0) == 0)
    {
        setStatus("Preset slot " + std::to_string(g_menu.presetSlot) + " is empty", 5000);
        return;
    }

    int mode = std::clamp(readPresetInt(section.c_str(), "Mode", static_cast<int>(g_menu.mode)), 0, 3);
    int battleType = std::clamp(readPresetInt(section.c_str(), "BattleType", static_cast<int>(g_menu.battleType)), 0, 2);
    g_menu.mode = static_cast<BattleMode>(mode);
    g_menu.battleType = static_cast<BattleType>(battleType);
    g_menu.killLimit = clampDeathmatchKillLimitValue(readPresetInt(section.c_str(), "KillLimit", g_menu.killLimit));
    g_menu.freeForAllSpectate = readPresetInt(section.c_str(), "FreeForAllSpectate", g_menu.freeForAllSpectate ? 1 : 0) != 0;
    g_menu.battleRoyaleTeamSize = std::clamp(readPresetInt(section.c_str(), "BattleRoyaleTeamSize", g_menu.battleRoyaleTeamSize), 1, 4);

    for (int teamIndex = 0; teamIndex < kTeamCount; ++teamIndex)
    {
        TeamSetup& team = g_teams[static_cast<size_t>(teamIndex)];
        std::string teamPrefix = "Team" + std::to_string(teamIndex);
        int relation = std::clamp(readPresetInt(section.c_str(), presetKey(teamPrefix, "Relation").c_str(), static_cast<int>(team.playerRelation)), 0, 2);
        team.playerRelation = static_cast<PlayerRelation>(relation);
        team.manualSpawnSet = readPresetInt(section.c_str(), presetKey(teamPrefix, "ManualSpawnSet").c_str(), 0) != 0;
        team.manualSpawn.x = readPresetFloat(section.c_str(), presetKey(teamPrefix, "ManualSpawnX").c_str(), team.manualSpawn.x);
        team.manualSpawn.y = readPresetFloat(section.c_str(), presetKey(teamPrefix, "ManualSpawnY").c_str(), team.manualSpawn.y);
        team.manualSpawn.z = readPresetFloat(section.c_str(), presetKey(teamPrefix, "ManualSpawnZ").c_str(), team.manualSpawn.z);
        team.sets.clear();

        int teamSetCount = readPresetInt(section.c_str(), presetKey(teamPrefix, "SetCount").c_str(), -1);
        if (teamSetCount >= 0)
        {
            teamSetCount = std::clamp(teamSetCount, 0, 64);
            for (int setIndex = 0; setIndex < teamSetCount; ++setIndex)
            {
                TeamRosterSlot slot = readPresetRosterSlot(section, teamPrefix + "Set" + std::to_string(setIndex));
                if (effectiveSlotCount(slot) > 0)
                    team.sets.push_back(slot);
            }
        }
        else
        {
            for (int slotIndex = 0; slotIndex < kRosterSlotCount; ++slotIndex)
            {
                TeamRosterSlot slot = readPresetRosterSlot(section, teamPrefix + "Slot" + std::to_string(slotIndex));
                if (effectiveSlotCount(slot) > 0)
                    team.sets.push_back(slot);
            }
        }
    }

    g_battleRoyaleSets.clear();
    int setCount = std::clamp(readPresetInt(section.c_str(), "BattleRoyaleSetCount", 0), 0, 64);
    for (int i = 0; i < setCount; ++i)
    {
        TeamRosterSlot slot = readPresetRosterSlot(section, "BattleRoyaleSet" + std::to_string(i));
        if (effectiveSlotCount(slot) > 0)
            g_battleRoyaleSets.push_back(slot);
    }
    g_menu.battleRoyaleDraft = readPresetRosterSlot(section, "Draft");
    if (effectiveSlotCount(g_menu.battleRoyaleDraft) <= 0)
    {
        g_menu.battleRoyaleDraft.count = 1;
        g_menu.battleRoyaleDraft.pedSet = 1;
        g_menu.battleRoyaleDraft.difficulty = Difficulty::Medium;
    }

    g_menu.team = std::clamp(g_menu.team, 0, kTeamCount - 1);
    g_menu.slot = 0;
    g_menu.battleRoyaleSet = 0;
    if (!freeForAllMode(g_menu.mode))
        loadSelectedTeamSetIntoDraft(false);
    g_menu.row = 0;
    clampCurrentSelection();
    setStatus("Loaded battle preset slot " + std::to_string(g_menu.presetSlot), 5000);
}

void saveCurrentSettingsToIni(bool showStatus)
{
    writeIniString("BattleModifiers", "ForcePlayerSpectator", g_settings.forcePlayerSpectator ? "true" : "false");
    writeIniString("BattleModifiers", "EnableManualTeamSpawns", g_settings.enableManualTeamSpawns ? "true" : "false");
    writeIniString("BattleModifiers", "NeutralsFriendlyUntilAttacked", g_settings.neutralsFriendlyUntilAttacked ? "true" : "false");
    writeIniFloat("BattleModifiers", "SpectatorMaxTargetDistance", g_settings.spectatorMaxTargetDistance);
    writeIniString("BattleModifiers", "NoDeadEyeDuringBattles", g_settings.noDeadEyeDuringBattles ? "true" : "false");
    writeIniString("BattleModifiers", "NeverWantedDuringBattles", g_settings.neverWantedDuringBattles ? "true" : "false");
    writeIniInt("BattleModifiers", "StartCountdownSeconds", g_settings.startCountdownSeconds);
    writeIniFloat("Battle", "FirearmSpawnDistance", g_settings.firearmSpawnDistance);
    writeIniFloat("Battle", "MeleeSpawnDistance", g_settings.meleeSpawnDistance);
    writeIniFloat("Battle", "UnarmedSpawnDistance", g_settings.unarmedSpawnDistance);
    writeIniFloat("Battle", "CleanupDistance", g_settings.cleanupDistance);
    writeIniInt("Battle", "MaxTeamCount", g_settings.maxTeamCount);
    writeIniInt("Deathmatch", "DefaultKillLimit", g_settings.defaultDeathmatchKillLimit);
    writeIniInt("Deathmatch", "NpcRespawnDelayMs", static_cast<int>(g_settings.npcDeathmatchRespawnDelayMs));
    writeIniString("Deathmatch", "RespawnTeamDeathmatchAtOriginalSpawn", g_settings.respawnTeamDeathmatchAtOriginalSpawn ? "true" : "false");
    writeIniString("DeathmatchPerformance", "ImmediateNpcCorpseCleanup", g_settings.immediateDeathmatchNpcCorpseCleanup ? "true" : "false");
    writeIniInt("DeathmatchPerformance", "CorpseVisibleMs", static_cast<int>(g_settings.deathmatchCorpseVisibleMs));
    writeIniInt("DeathmatchPerformance", "MaximumRespawnsPerFrame", g_settings.deathmatchMaximumRespawnsPerFrame);
    writeIniInt("DeathmatchPerformance", "MinimumRespawnGapMs", static_cast<int>(g_settings.deathmatchMinimumRespawnGapMs));
    writeIniInt("DeathmatchPerformance", "SnapshotRefreshMs", static_cast<int>(g_settings.deathmatchSnapshotRefreshMs));
    writeIniInt("DeathmatchPerformance", "MaximumFullRetargetsPerFrame", g_settings.deathmatchMaximumFullRetargetsPerFrame);
    writeIniInt("DeathmatchPerformance", "LargeDeathmatchThreshold", g_settings.largeDeathmatchThreshold);
    writeIniInt("DeathmatchPerformance", "LargeDeathmatchCombatUpdateMs", static_cast<int>(g_settings.largeDeathmatchCombatUpdateMs));
    writeIniInt("DeathmatchPerformance", "LargeDeathmatchBlipValidationMs", static_cast<int>(g_settings.largeDeathmatchBlipValidationMs));
    writeIniInt("DeathmatchPerformance", "LargeDeathmatchDynamicRepairMs", static_cast<int>(g_settings.largeDeathmatchDynamicRepairMs));
    writeIniInt("DeathmatchPerformance", "SoloFfaIdleCheckMs", static_cast<int>(g_settings.soloFfaIdleCheckMs));
    writeIniInt("DeathmatchPerformance", "SoloFfaIdleThresholdMs", static_cast<int>(g_settings.soloFfaIdleThresholdMs));
    writeIniString("DeathmatchPerformance", "PreventPersistentDroppedWeapons", g_settings.preventPersistentDroppedWeapons ? "true" : "false");
    writeIniString("CombatRecovery", "EnableIdleWatchdog", g_settings.enableIdleWatchdog ? "true" : "false");
    writeIniInt("CombatRecovery", "OrdinaryCheckIntervalMs", static_cast<int>(g_settings.ordinaryIdleCheckIntervalMs));
    writeIniInt("CombatRecovery", "OrdinaryIdleThresholdMs", static_cast<int>(g_settings.ordinaryIdleThresholdMs));
    writeIniInt("CombatRecovery", "OrdinaryConsecutiveChecks", g_settings.ordinaryIdleConsecutiveChecks);
    writeIniInt("CombatRecovery", "SoftRecoveryDelayMs", static_cast<int>(g_settings.idleSoftRecoveryDelayMs));
    writeIniInt("CombatRecovery", "HardRecoveryCooldownMs", static_cast<int>(g_settings.idleHardRecoveryCooldownMs));
    writeIniFloat("CombatRecovery", "RepositionMinDistance", g_settings.idleRepositionMinDistance);
    writeIniFloat("CombatRecovery", "RepositionMaxDistance", g_settings.idleRepositionMaxDistance);
    writeIniString("CombatRecovery", "AllowForcedTargetChange", g_settings.idleAllowForcedTargetChange ? "true" : "false");
    writeIniString("Performance", "EnableCorpseCleanup", g_settings.enableCorpseCleanup ? "true" : "false");
    writeIniInt("Performance", "NormalCorpseLifetimeMs", static_cast<int>(g_settings.normalCorpseLifetimeMs));
    writeIniInt("Performance", "EliteCorpseLifetimeMs", static_cast<int>(g_settings.eliteCorpseLifetimeMs));
    writeIniInt("Performance", "MaximumCorpseLifetimeMs", static_cast<int>(g_settings.maximumCorpseLifetimeMs));
    writeIniInt("Performance", "CorpseCleanupCheckMs", static_cast<int>(g_settings.corpseCleanupCheckMs));
    writeIniFloat("Performance", "CorpseCleanupMinPlayerDistance", g_settings.corpseCleanupMinPlayerDistance);
    writeIniInt("Performance", "PreferredMaximumCorpses", g_settings.preferredMaximumCorpses);
    writeIniInt("Performance", "HardMaximumCorpses", g_settings.hardMaximumCorpses);
    writeIniString("Performance", "CleanTrackedDroppedWeapons", g_settings.cleanTrackedDroppedWeapons ? "true" : "false");
    writeIniString("Performance", "EnableDistantBattleSimulation", g_settings.enableDistantBattleSimulation ? "true" : "false");
    writeIniFloat("Performance", "DistantBattleSimulationDistance", g_settings.distantBattleSimulationDistance);
    writeIniInt("Performance", "DistantBattleSimulationDelayMs", static_cast<int>(g_settings.distantBattleSimulationDelayMs));
    writeIniInt("Performance", "DistantBattleSimulationTickMs", static_cast<int>(g_settings.distantBattleSimulationTickMs));
    flushBattleCreatorIni();
    if (showStatus)
        setStatus("Saved settings to BattleCreator.ini", 5000);
}

Difficulty randomStandardDifficulty()
{
    int roll = randomRange(0, 100);
    if (roll < 18)
        return Difficulty::Easy;
    if (roll < 58)
        return Difficulty::Medium;
    if (roll < 84)
        return Difficulty::Hard;
    return Difficulty::Extreme;
}

int randomPedSet()
{
    return randomRange(0, static_cast<int>(g_pedSets.size()) - 1);
}

int randomUnusedIndex(std::vector<bool>& used)
{
    std::vector<int> choices;
    for (int i = 0; i < static_cast<int>(used.size()); ++i)
    {
        if (!used[static_cast<size_t>(i)])
            choices.push_back(i);
    }
    if (choices.empty())
        return randomRange(0, static_cast<int>(used.size()) - 1);

    int choice = choices[static_cast<size_t>(randomRange(0, static_cast<int>(choices.size()) - 1))];
    used[static_cast<size_t>(choice)] = true;
    return choice;
}

TeamRosterSlot randomBattleSlot(std::vector<bool>& usedBosses, std::vector<bool>& usedSpecials, bool allowNamed)
{
    TeamRosterSlot slot{};
    int roll = randomRange(0, 100);
    if (roll < 13)
    {
        slot.count = 1;
        slot.difficulty = Difficulty::Bosses;
        slot.boss = randomUnusedIndex(usedBosses);
    }
    else if (roll < 27)
    {
        slot.count = 1;
        slot.difficulty = Difficulty::Special;
        slot.special = randomUnusedIndex(usedSpecials);
    }
    else
    {
        slot.difficulty = randomStandardDifficulty();
        slot.pedSet = randomPedSet();
        if (!allowNamed && isUniqueNamedPedSet(slot.pedSet))
            slot.pedSet = randomRange(0, kNamedGangPedSetIndex - 1);
        int maxCount = maxCountForSlot(slot);
        int minCount = std::min(maxCount, randomRange(4, 8));
        int highBase = std::max(minCount, std::min(maxCount, g_settings.maxTeamCount));
        int highCount = randomRange(minCount, highBase);
        if (highCount < minCount)
            highCount = minCount;
        slot.count = randomRange(minCount, highCount);
    }
    clampRosterSlot(slot);
    return slot;
}

void randomizeTeamBattle()
{
    std::vector<bool> usedBosses(kBosses.size(), false);
    std::vector<bool> usedSpecials(kSpecialPeds.size(), false);
    clearAllTeamRosters();
    g_battleRoyaleSets.clear();
    g_menu.battleType = static_cast<BattleType>(randomRange(0, 2));

    int activeTeams = randomRange(2, kTeamCount);
    for (int teamIndex = 0; teamIndex < kTeamCount; ++teamIndex)
    {
        TeamSetup& team = g_teams[static_cast<size_t>(teamIndex)];
        if (teamIndex == 0)
            team.playerRelation = PlayerRelation::Friendly;
        else
            team.playerRelation = teamIndex < activeTeams ? PlayerRelation::Hostile : PlayerRelation::Neutral;

        if (teamIndex >= activeTeams)
            continue;

        int slotCount = randomRange(1, 3);
        for (int slotIndex = 0; slotIndex < slotCount; ++slotIndex)
            team.sets.push_back(randomBattleSlot(usedBosses, usedSpecials, false));
    }

    if (deathmatchSelected())
        g_menu.killLimit = clampDeathmatchKillLimitValue(randomRange(20, 60));

    g_menu.team = 0;
    g_menu.slot = 0;
    loadSelectedTeamSetIntoDraft(false);
    g_menu.row = 0;
    setStatus(deathmatchSelected() ? "Randomized Team Deathmatch" : "Randomized Team Survival", 6500);
}

void randomizeFreeForAllBattle()
{
    std::vector<bool> usedBosses(kBosses.size(), false);
    std::vector<bool> usedSpecials(kSpecialPeds.size(), false);
    g_battleRoyaleSets.clear();
    clearAllTeamRosters();
    g_menu.battleType = static_cast<BattleType>(randomRange(0, 2));
    g_menu.battleRoyaleTeamSize = randomRange(1, 4);
    g_menu.freeForAllSpectate = false;

    int setCount = randomRange(3, 6);
    for (int i = 0; i < setCount; ++i)
    {
        TeamRosterSlot slot = randomBattleSlot(usedBosses, usedSpecials, true);
        if (effectiveSlotCount(slot) > 0)
            g_battleRoyaleSets.push_back(slot);
    }

    if (g_battleRoyaleSets.empty())
    {
        TeamRosterSlot fallback{};
        fallback.count = 12;
        fallback.pedSet = 1;
        fallback.difficulty = Difficulty::Medium;
        g_battleRoyaleSets.push_back(fallback);
    }

    if (deathmatchSelected())
        g_menu.killLimit = clampDeathmatchKillLimitValue(randomRange(20, 60));

    g_menu.battleRoyaleDraft = g_battleRoyaleSets.front();
    g_menu.battleRoyaleSet = 0;
    g_menu.slot = 0;
    g_menu.row = 0;
    setStatus(deathmatchSelected() ? "Randomized Free For All" : "Randomized Battle Royale", 6500);
}

void randomizeCurrentMode()
{
    if (freeForAllSelected())
        randomizeFreeForAllBattle();
    else
        randomizeTeamBattle();
    clampCurrentSelection();
}

void applyMixedExampleToCurrentTeam()
{
    clearRosterSlots(g_menu.team);
    setRosterSlot(g_menu.team, 0, 10, 1, Difficulty::Medium);
    setRosterSlot(g_menu.team, 1, 1, 1, Difficulty::Bosses, 1);
    g_menu.slot = 0;
    loadSelectedTeamSetIntoDraft(false);
    setStatus("Current team: 10 medium O'Driscolls + boss Dutch", 6000);
}

void applyFreeForAllExample()
{
    bool keepDeathmatch = g_menu.mode == BattleMode::FreeForAllDeathmatch;
    g_menu.mode = keepDeathmatch ? BattleMode::FreeForAllDeathmatch : BattleMode::FreeForAll;
    g_menu.battleType = BattleType::AllWeapons;
    g_menu.freeForAllSpectate = false;
    g_battleRoyaleSets.clear();

    TeamRosterSlot odriscolls{};
    odriscolls.count = 20;
    odriscolls.pedSet = 1;
    odriscolls.difficulty = Difficulty::Medium;
    clampRosterSlot(odriscolls);
    g_battleRoyaleSets.push_back(odriscolls);

    TeamRosterSlot army{};
    army.count = 20;
    army.pedSet = 9;
    army.difficulty = Difficulty::Medium;
    clampRosterSlot(army);
    g_battleRoyaleSets.push_back(army);

    TeamRosterSlot john{};
    john.count = 1;
    john.difficulty = Difficulty::Bosses;
    john.boss = 0;
    clampRosterSlot(john);
    g_battleRoyaleSets.push_back(john);

    TeamRosterSlot gang{};
    gang.count = 5;
    gang.pedSet = kNamedGangPedSetIndex;
    gang.difficulty = Difficulty::Medium;
    clampRosterSlot(gang);
    g_battleRoyaleSets.push_back(gang);

    g_menu.battleRoyaleDraft = odriscolls;
    g_menu.battleRoyaleSet = 0;
    g_menu.slot = 0;
    g_menu.row = 0;
        setStatus(keepDeathmatch ? "Applied Free For All example" : "Applied Battle Royale example", 7000);
}

void applyPreset()
{
    g_menu.mode = BattleMode::Teams;
    switch (g_menu.preset)
    {
    case BattlePreset::PlayerFight:
        g_menu.battleType = BattleType::AllWeapons;
        setTeam(0, PlayerRelation::Friendly);
        setRosterSlot(0, 0, 20, 1, Difficulty::Medium);
        setTeam(1, PlayerRelation::Hostile);
        setRosterSlot(1, 0, 20, 3, Difficulty::Medium);
        setRosterSlot(1, 1, 1, 3, Difficulty::Bosses, 0);
        setTeam(2, PlayerRelation::Hostile);
        setRosterSlot(2, 0, 20, 5, Difficulty::Medium);
        setRosterSlot(2, 1, 1, 5, Difficulty::Bosses, 1);
        setTeam(3, PlayerRelation::Hostile);
        setRosterSlot(3, 0, 20, 6, Difficulty::Medium);
        setRosterSlot(3, 1, 1, 6, Difficulty::Bosses, 2);
        g_menu.team = 0;
        break;
    case BattlePreset::SpectatorDuel:
        g_menu.battleType = BattleType::AllWeapons;
        setTeam(0, 0, 0, Difficulty::Medium, PlayerRelation::Friendly);
        setTeam(1, 0, 1, Difficulty::Medium, PlayerRelation::Hostile);
        setTeam(2, 8, 2, Difficulty::Hard, PlayerRelation::Neutral);
        setTeam(3, 8, 3, Difficulty::Hard, PlayerRelation::Neutral);
        g_menu.team = 2;
        break;
    case BattlePreset::FourWayChaos:
        g_menu.battleType = BattleType::AllWeapons;
        setTeam(0, 4, 0, Difficulty::Medium, PlayerRelation::Friendly);
        setTeam(1, 4, 1, Difficulty::Medium, PlayerRelation::Hostile);
        setTeam(2, 4, 2, Difficulty::Hard, PlayerRelation::Neutral);
        setTeam(3, 4, 3, Difficulty::Hard, PlayerRelation::Neutral);
        g_menu.team = 0;
        break;
    case BattlePreset::BossShowdown:
        g_menu.battleType = BattleType::AllWeapons;
        setTeam(0, 1, 0, Difficulty::Bosses, PlayerRelation::Friendly, 0);
        setTeam(1, 1, 1, Difficulty::Bosses, PlayerRelation::Hostile, 2);
        setTeam(2, 1, 2, Difficulty::Bosses, PlayerRelation::Neutral, 1);
        setTeam(3, 0, 3, Difficulty::Extreme, PlayerRelation::Neutral);
        g_menu.team = 0;
        break;
    }

    g_menu.slot = 0;
    loadSelectedTeamSetIntoDraft(false);
    setStatus(std::string("Applied preset: ") + presetName(g_menu.preset), 5000);
}

void drawMenu()
{
    if (g_menu.settingsPage)
    {
        drawSettingsMenu();
        return;
    }

    GRAPHICS::DRAW_RECT(0.45f, 0.47f, 0.76f, 0.72f, 8, 10, 12, 205, true, true);
    GRAPHICS::DRAW_RECT(0.45f, 0.151f, 0.76f, 0.058f, 120, 32, 32, 230, true, true);

    drawTextLine("BATTLE CREATOR", 0.075f, 0.126f, 0.42f, 245, 236, 218, 255);
    const bool ffa = freeForAllSelected();
    drawTextLine(
        ffa ? "F9 close | K spectate | N random | R reload INI" : "F9 close | K spectate | 1-4 team | N random | R reload INI",
        0.075f,
        0.174f,
        0.245f,
        210,
        205,
        190,
        235);

    const TeamSetup& team = g_teams[static_cast<size_t>(g_menu.team)];
    const TeamRosterSlot& slot = selectedSlotConst();
    const bool boss = slot.difficulty == Difficulty::Bosses;
    const bool special = slot.difficulty == Difficulty::Special;
    std::string unitSelector = "Ped set: ";
    unitSelector += g_pedSets[static_cast<size_t>(slot.pedSet)].name;
    if (boss)
    {
        unitSelector = "Boss: ";
        unitSelector += kBosses[static_cast<size_t>(slot.boss)].name;
    }
    else if (special)
    {
        unitSelector = "Special: ";
        unitSelector += kSpecialPeds[static_cast<size_t>(slot.special)].name;
    }

    std::string playerMode = ffa ?
        std::string("Player: ") + freeForAllPlayerName(g_menu.freeForAllSpectate) :
        std::string("Player relation: ") + relationName(team.playerRelation);
    std::string editTeamText = "Edit team: Team " + std::to_string(g_menu.team + 1);
    std::string selectedTeamSet = team.sets.empty() ? "None" : teamSetSummary(g_menu.team, std::clamp(g_menu.slot, 0, static_cast<int>(team.sets.size()) - 1));

    std::vector<std::string> rows;
    rows.reserve(kMaxRows);
    auto addRow = [&](int logicalRow, const std::string& text) {
        int visibleRow = visibleMenuRow(logicalRow);
        rows.push_back(selectedPrefix(visibleRow) + text);
    };

    addRow(0, "Battle mode: " + std::string(battleModeName(g_menu.mode)));
    addRow(1, "Battle type: " + std::string(battleTypeName(g_menu.battleType)));
    addRow(2, std::string(ffa ? "Spawn radius: " : "Spawn distance: ") + spawnDistanceText());
    if (showKillLimitRow())
        addRow(3, "Kill limit: " + killLimitText());
    if (ffa)
    {
        std::string selectedSet = g_battleRoyaleSets.empty() ? "None" : battleRoyaleSetSummary(std::clamp(g_menu.battleRoyaleSet, 0, static_cast<int>(g_battleRoyaleSets.size()) - 1));
        addRow(4, std::string("Team size: ") + battleRoyaleTeamSizeName(g_menu.battleRoyaleTeamSize));
        addRow(5, playerMode);
        addRow(6, "Set difficulty: " + std::string(difficultyName(slot.difficulty)));
        addRow(7, unitSelector);
        addRow(8, "Set count: " + countText(slot));
        addRow(9, "Add set");
        addRow(10, "Selected set: " + selectedSet);
        addRow(11, "Update selected set");
        addRow(12, "Remove selected set");
        addRow(13, "Clear all sets");
        addRow(14, deathmatchSelected() ? "Start Free For All" : "Start Battle Royale");
        addRow(15, "Clear current battle");
        addRow(16, "Settings & presets");
    }
    else
    {
        addRow(4, editTeamText);
        if (showManualTeamSpawnRows())
        {
            const TeamSetup& selectedTeam = g_teams[static_cast<size_t>(g_menu.team)];
            addRow(5, selectedTeam.manualSpawnSet ? "Set Spawn: update here" : "Set Spawn");
            addRow(6, "Clear Spawn");
        }
        addRow(7, playerMode);
        addRow(8, "Set difficulty: " + std::string(difficultyName(slot.difficulty)));
        addRow(9, unitSelector);
        addRow(10, "Set count: " + countText(slot));
        addRow(11, "Add set to team");
        addRow(12, "Selected set: " + selectedTeamSet);
        addRow(13, "Update selected set");
        addRow(14, "Remove selected set");
        addRow(15, "Clear team sets");
        addRow(16, deathmatchSelected() ? "Start Team Deathmatch" : "Start Team Survival");
        addRow(17, "Clear current battle");
        addRow(18, "Settings & presets");
    }

    float y = 0.214f;
    float rowStep = rows.size() > 17 ? 0.029f : (rows.size() > 15 ? 0.031f : 0.034f);
    float normalScale = rows.size() > 17 ? 0.244f : 0.275f;
    float selectedScale = rows.size() > 17 ? 0.268f : 0.300f;
    for (int i = 0; i < static_cast<int>(rows.size()); ++i)
    {
        bool selected = g_menu.row == i;
        drawTextLine(rows[static_cast<size_t>(i)], 0.075f, y, selected ? selectedScale : normalScale, selected ? 255 : 225, selected ? 236 : 220, selected ? 178 : 205, 255);
        y += rowStep;
    }

    drawTextLine(ffa ? (deathmatchSelected() ? "Free For All Sets" : "Battle Royale Sets") : "Current Team Sets", 0.455f, 0.218f, 0.30f, 245, 236, 218, 255);
    if (ffa)
    {
        drawTextLine(battleRoyaleDraftSummary(), 0.455f, 0.256f, 0.245f, 255, 236, 178, 245);
        if (g_battleRoyaleSets.empty())
        {
            drawTextLine("No sets added", 0.455f, 0.302f, 0.245f, 205, 205, 195, 235);
        }
        else
        {
            int selected = std::clamp(g_menu.battleRoyaleSet, 0, static_cast<int>(g_battleRoyaleSets.size()) - 1);
            int first = std::max(0, selected - 4);
            int last = std::min(static_cast<int>(g_battleRoyaleSets.size()), first + 10);
            if (last - first < 10)
                first = std::max(0, last - 10);

            float setY = 0.302f;
            for (int i = first; i < last; ++i)
            {
                bool selectedLine = i == selected;
                drawTextLine(
                    battleRoyaleSetSummary(i),
                    0.455f,
                    setY,
                    0.225f,
                    selectedLine ? 255 : 205,
                    selectedLine ? 236 : 205,
                    selectedLine ? 178 : 195,
                    245);
                setY += 0.030f;
            }

            if (static_cast<int>(g_battleRoyaleSets.size()) > last)
                drawTextLine("+ more sets", 0.455f, setY, 0.205f, 205, 205, 195, 225);
        }
    }
    else
    {
        drawTextLine(battleRoyaleDraftSummary(), 0.455f, 0.256f, 0.245f, 255, 236, 178, 245);
        if (team.sets.empty())
        {
            drawTextLine("No sets added to this team", 0.455f, 0.302f, 0.245f, 205, 205, 195, 235);
        }
        else
        {
            int selected = std::clamp(g_menu.slot, 0, static_cast<int>(team.sets.size()) - 1);
            int first = std::max(0, selected - 4);
            int last = std::min(static_cast<int>(team.sets.size()), first + 7);
            if (last - first < 7)
                first = std::max(0, last - 7);

            float setY = 0.302f;
            for (int i = first; i < last; ++i)
            {
                bool selectedLine = i == selected;
                drawTextLine(
                    teamSetSummary(g_menu.team, i),
                    0.455f,
                    setY,
                    0.225f,
                    selectedLine ? 255 : 205,
                    selectedLine ? 236 : 205,
                    selectedLine ? 178 : 195,
                    245);
                setY += 0.030f;
            }

            if (static_cast<int>(team.sets.size()) > last)
                drawTextLine("+ more sets", 0.455f, setY, 0.205f, 205, 205, 195, 225);
        }
    }

    if (!ffa)
    {
        drawTextLine("Teams", 0.455f, 0.590f, 0.30f, 245, 236, 218, 255);
        float summaryY = 0.628f;
        for (int i = 0; i < kTeamCount; ++i)
        {
            bool selected = i == g_menu.team;
            drawTextLine(teamSummary(i), 0.455f, summaryY, 0.245f, selected ? 255 : 205, selected ? 236 : 205, selected ? 178 : 195, 245);
            summaryY += 0.034f;
        }
    }

    std::string status = g_runtime.battleActive ? battleSummaryText() : (g_runtime.status.empty() ? "Ready" : g_runtime.status);
    if (!status.empty() && status != "Battle Creator opened")
        drawTextLine(status, 0.455f, 0.796f, 0.245f, 220, 235, 220, 245);
}

void drawLeaderboard()
{
    int total = static_cast<int>(g_runtime.leaderboardLines.size());
    if (total <= 0)
        return;

    int columns = total > 18 ? 2 : 1;
    int rows = (total + columns - 1) / columns;
    bool trimmed = g_runtime.leaderboardTotal > total;
    float lineStep = columns == 1 ? 0.030f : 0.0215f;
    if (rows > 0)
        lineStep = std::min(lineStep, 0.745f / static_cast<float>(rows));
    float scale = columns == 1 ? 0.255f : 0.185f;
    float height = std::min(0.90f, 0.175f + rows * lineStep + (trimmed ? 0.035f : 0.0f));

    float panelWidth = 0.90f;
    float left = 0.50f - panelWidth * 0.5f + 0.03f;
    GRAPHICS::DRAW_RECT(0.50f, 0.08f + height * 0.5f, panelWidth, height, 8, 10, 12, 205, true, true);
    GRAPHICS::DRAW_RECT(0.50f, 0.101f, panelWidth, 0.055f, 120, 32, 32, 230, true, true);
    char header[96]{};
    std::snprintf(
        header,
        sizeof(header),
        "BATTLE LEADERBOARD - %s (%s toggle)",
        leaderboardModeName(g_runtime.leaderboardMode),
        kLeaderboardToggleKeyName);
    drawTextLine(header, left, 0.079f, 0.34f, 245, 236, 218, 255);

    float columnWidth = (panelWidth - 0.06f) / static_cast<float>(columns);
    for (int i = 0; i < total; ++i)
    {
        int column = i / rows;
        int row = i % rows;
        float x = left + columnWidth * static_cast<float>(column);
        float y = 0.145f + lineStep * static_cast<float>(row);
        drawTextLine(g_runtime.leaderboardLines[static_cast<size_t>(i)], x, y, scale, 225, 222, 205, 250);
    }

    if (trimmed)
    {
        char buffer[80]{};
        std::snprintf(buffer, sizeof(buffer), "Showing top %d of %d", total, g_runtime.leaderboardTotal);
        drawTextLine(buffer, left, 0.153f + lineStep * static_cast<float>(rows), 0.205f, 210, 205, 190, 235);
    }
}

std::string teamDeathmatchCompactScoreText()
{
    int limit = deathmatchKillLimit();
    bool showPlayer = g_runtime.playerWasParticipant && g_runtime.playerTeam >= 0;
    char buffer[192]{};
    if (limit <= 0)
    {
        if (showPlayer)
        {
            std::snprintf(
                buffer,
                sizeof(buffer),
                "You:%d  T1:%d  T2:%d  T3:%d  T4:%d",
                g_runtime.playerKills,
                teamKillScore(0),
                teamKillScore(1),
                teamKillScore(2),
                teamKillScore(3));
        }
        else
        {
            std::snprintf(
                buffer,
                sizeof(buffer),
                "T1:%d  T2:%d  T3:%d  T4:%d",
                teamKillScore(0),
                teamKillScore(1),
                teamKillScore(2),
                teamKillScore(3));
        }
        return buffer;
    }

    if (showPlayer)
    {
        std::snprintf(
            buffer,
            sizeof(buffer),
            "You:%d  T1:%d/%d  T2:%d/%d  T3:%d/%d  T4:%d/%d",
            g_runtime.playerKills,
            teamKillScore(0), limit,
            teamKillScore(1), limit,
            teamKillScore(2), limit,
            teamKillScore(3), limit);
    }
    else
    {
        std::snprintf(
            buffer,
            sizeof(buffer),
            "T1:%d/%d  T2:%d/%d  T3:%d/%d  T4:%d/%d",
            teamKillScore(0), limit,
            teamKillScore(1), limit,
            teamKillScore(2), limit,
            teamKillScore(3), limit);
    }
    return buffer;
}

void refreshCompactBattleHud(DWORD t, bool force = false)
{
    if (!g_runtime.battleActive)
    {
        g_runtime.compactHudLine1.clear();
        g_runtime.compactHudLine2.clear();
        g_runtime.compactHudTwoLine = false;
        g_runtime.compactHudNextRefreshAt = 0;
        return;
    }

    if (!force && t < g_runtime.compactHudNextRefreshAt && !g_runtime.compactHudLine1.empty())
        return;

    int aliveCombatants = aliveFighterCount() + (playerAliveInBattle() ? 1 : 0);
    char line1[160]{};
    std::string line2;
    bool twoLine = false;

    if (deathmatchActive())
    {
        int limit = deathmatchKillLimit();
        if (g_runtime.freeForAll)
        {
            if (limit <= 0)
                std::snprintf(line1, sizeof(line1), "Free For All - Endless  Alive:%d", aliveCombatants);
            else
                std::snprintf(line1, sizeof(line1), "Free For All - Goal:%d  Alive:%d", limit, aliveCombatants);
            line2 = freeForAllDeathmatchScoreText();
            twoLine = true;
        }
        else
        {
            if (limit <= 0)
                std::snprintf(line1, sizeof(line1), "Team Deathmatch - Endless  Alive:%d", aliveCombatants);
            else
                std::snprintf(line1, sizeof(line1), "Team Deathmatch - Goal:%d  Alive:%d", limit, aliveCombatants);
            line2 = teamDeathmatchCompactScoreText();
            twoLine = true;
        }
    }
    else
    {
        std::string summary = battleSummaryText();
        std::snprintf(line1, sizeof(line1), "%s", summary.c_str());
        bool showPlayerKills = g_runtime.playerWasParticipant && !g_runtime.freeForAllSpectate;
        if (showPlayerKills)
        {
            char killsBuffer[64]{};
            std::snprintf(killsBuffer, sizeof(killsBuffer), "Your kills: %d", g_runtime.playerKills);
            line2 = killsBuffer;
            twoLine = true;
        }
    }

    g_runtime.compactHudLine1 = line1;
    g_runtime.compactHudLine2 = line2;
    g_runtime.compactHudTwoLine = twoLine && !line2.empty();
    g_runtime.compactHudNextRefreshAt = t + kCompactHudRefreshMs;
}

void drawCompactStatus()
{
    if (!g_runtime.leaderboardLines.empty())
    {
        drawLeaderboard();
        return;
    }

    DWORD t = now();
    if (g_runtime.battleActive)
    {
        refreshCompactBattleHud(t);
        bool twoLineStatus = g_runtime.compactHudTwoLine;
        float statusCenterY = twoLineStatus ? 0.090f : 0.075f;
        float statusHeight = twoLineStatus ? 0.095f : 0.065f;
        float panelWidth = deathmatchActive() ? 0.46f : 0.36f;
        GRAPHICS::DRAW_RECT(0.23f, statusCenterY, panelWidth, statusHeight, 8, 10, 12, 170, true, true);
        drawTextLine(g_runtime.compactHudLine1, 0.055f, 0.054f, 0.29f, 240, 235, 220, 245);
        if (twoLineStatus)
            drawTextLine(g_runtime.compactHudLine2, 0.055f, 0.086f, 0.215f, 240, 235, 220, 245);
        Fighter* target = spectatorTarget();
        if (g_runtime.spectatorCameraActive && target)
        {
            std::string targetName = target->displayName;
            if (targetName.size() > 22)
                targetName = targetName.substr(0, 19) + "...";
            char buffer[160]{};
            std::snprintf(
                buffer,
                sizeof(buffer),
                "Spec: %s  K:%d  <-/->  K exit",
                targetName.c_str(),
                target->kills);
            float specCenterY = twoLineStatus ? 0.162f : 0.126f;
            float specTextY = twoLineStatus ? 0.147f : 0.111f;
            GRAPHICS::DRAW_RECT(0.23f, specCenterY, panelWidth, 0.040f, 8, 10, 12, 170, true, true);
            drawTextLine(buffer, 0.055f, specTextY, 0.205f, 240, 235, 220, 245);
        }
        return;
    }

    if (g_runtime.status.empty() || t > g_runtime.lastStatusUntil)
        return;

    GRAPHICS::DRAW_RECT(0.23f, 0.075f, 0.36f, 0.065f, 8, 10, 12, 170, true, true);
    drawTextLine(g_runtime.status, 0.055f, 0.054f, 0.29f, 240, 235, 220, 245);
}

void wrapInt(int& value, int delta, int count)
{
    if (count <= 0)
        return;
    value = (value + delta) % count;
    if (value < 0)
        value += count;
}

void clampCurrentSelection()
{
    if (g_menu.settingsPage)
    {
        g_menu.row = std::clamp(g_menu.row, 0, kSettingsMenuRows - 1);
        return;
    }

    g_menu.row = std::clamp(g_menu.row, 0, menuRowCount() - 1);
    g_menu.killLimit = clampDeathmatchKillLimitValue(g_menu.killLimit);
    clampRosterSlot(g_menu.battleRoyaleDraft);
    if (freeForAllSelected())
    {
        g_menu.slot = 0;
    }
    else
    {
        g_menu.team = std::clamp(g_menu.team, 0, kTeamCount - 1);
        const TeamSetup& team = g_teams[static_cast<size_t>(g_menu.team)];
        if (!team.sets.empty())
            g_menu.slot = std::clamp(g_menu.slot, 0, static_cast<int>(team.sets.size()) - 1);
        else
            g_menu.slot = 0;
    }
    if (!g_battleRoyaleSets.empty())
        g_menu.battleRoyaleSet = std::clamp(g_menu.battleRoyaleSet, 0, static_cast<int>(g_battleRoyaleSets.size()) - 1);
    else
        g_menu.battleRoyaleSet = 0;
}

void adjustSelected(int direction)
{
    if (g_menu.settingsPage)
    {
        adjustSettingsSelected(direction);
        clampCurrentSelection();
        return;
    }

    TeamSetup& team = g_teams[static_cast<size_t>(g_menu.team)];
    TeamRosterSlot& slot = selectedSlot();
    bool ffa = freeForAllSelected();
    int row = logicalMenuRow(g_menu.row);

    switch (row)
    {
    case 0:
    {
        int mode = static_cast<int>(g_menu.mode);
        wrapInt(mode, direction, 4);
        g_menu.mode = static_cast<BattleMode>(mode);
        break;
    }
    case 1:
    {
        int type = static_cast<int>(g_menu.battleType);
        wrapInt(type, direction, 3);
        g_menu.battleType = static_cast<BattleType>(type);
        break;
    }
    case 2:
        adjustSpawnDistance(direction);
        break;
    case 3:
    {
        if (deathmatchSelected())
        {
            int step = (GetAsyncKeyState(VK_SHIFT) & 0x8000) ? 10 : 1;
            g_menu.killLimit = clampDeathmatchKillLimitValue(g_menu.killLimit + direction * step);
        }
        break;
    }
    case 4:
        if (ffa)
        {
            g_menu.battleRoyaleTeamSize += direction;
            if (g_menu.battleRoyaleTeamSize > 4)
                g_menu.battleRoyaleTeamSize = 1;
            else if (g_menu.battleRoyaleTeamSize < 1)
                g_menu.battleRoyaleTeamSize = 4;
            break;
        }
        wrapInt(g_menu.team, direction, kTeamCount);
        g_menu.slot = 0;
        loadSelectedTeamSetIntoDraft(false);
        break;
    case 5:
        if (ffa)
            g_menu.freeForAllSpectate = !g_menu.freeForAllSpectate;
        break;
    case 6:
        if (ffa)
        {
            int difficulty = static_cast<int>(slot.difficulty);
            wrapInt(difficulty, direction, static_cast<int>(kDifficulty.size()));
            slot.difficulty = static_cast<Difficulty>(difficulty);
        }
        break;
    case 7:
        if (ffa)
        {
            if (slot.difficulty == Difficulty::Bosses)
                wrapInt(slot.boss, direction, static_cast<int>(kBosses.size()));
            else if (slot.difficulty == Difficulty::Special)
                wrapInt(slot.special, direction, static_cast<int>(kSpecialPeds.size()));
            else
                wrapInt(slot.pedSet, direction, static_cast<int>(g_pedSets.size()));
        }
        else
        {
            int relation = static_cast<int>(team.playerRelation);
            wrapInt(relation, direction, 3);
            team.playerRelation = static_cast<PlayerRelation>(relation);
        }
        break;
    case 8:
        if (ffa)
        {
            int step = (GetAsyncKeyState(VK_SHIFT) & 0x8000) ? 5 : 1;
            slot.count += direction * step;
        }
        else
        {
            int difficulty = static_cast<int>(slot.difficulty);
            wrapInt(difficulty, direction, static_cast<int>(kDifficulty.size()));
            slot.difficulty = static_cast<Difficulty>(difficulty);
        }
        break;
    case 9:
        if (!ffa)
        {
            if (slot.difficulty == Difficulty::Bosses)
                wrapInt(slot.boss, direction, static_cast<int>(kBosses.size()));
            else if (slot.difficulty == Difficulty::Special)
                wrapInt(slot.special, direction, static_cast<int>(kSpecialPeds.size()));
            else
                wrapInt(slot.pedSet, direction, static_cast<int>(g_pedSets.size()));
        }
        break;
    case 10:
        if (ffa)
        {
            if (!g_battleRoyaleSets.empty())
            {
                wrapInt(g_menu.battleRoyaleSet, direction, static_cast<int>(g_battleRoyaleSets.size()));
                loadSelectedBattleRoyaleSetIntoDraft(false);
            }
        }
        else
        {
            int step = (GetAsyncKeyState(VK_SHIFT) & 0x8000) ? 5 : 1;
            slot.count += direction * step;
        }
        break;
    case 12:
        if (!ffa && !team.sets.empty())
        {
            wrapInt(g_menu.slot, direction, static_cast<int>(team.sets.size()));
            loadSelectedTeamSetIntoDraft(false);
        }
        break;
    default:
        break;
    }

    clampCurrentSelection();
}

void activateSelected()
{
    if (g_menu.settingsPage)
    {
        if (g_menu.row == 0)
        {
            g_menu.settingsPage = false;
            g_menu.row = 0;
        }
        else if (g_menu.row == 15)
            saveCurrentBattlePreset();
        else if (g_menu.row == 16)
            loadCurrentBattlePreset();
        else if (g_menu.row == 17)
            saveCurrentSettingsToIni(true);
        else if (g_menu.row == 18)
        {
            loadSettings();
            clampAllRosterSlots();
            clampCurrentSelection();
            setStatus("Reloaded Battle Creator INIs", 5000);
        }
        return;
    }

    int row = logicalMenuRow(g_menu.row);
    if (freeForAllSelected())
    {
        switch (row)
        {
        case 9:
            addBattleRoyaleSet();
            break;
        case 10:
            loadSelectedBattleRoyaleSetIntoDraft(true);
            break;
        case 11:
            updateSelectedBattleRoyaleSet();
            break;
        case 12:
            removeSelectedBattleRoyaleSet();
            break;
        case 13:
            clearBattleRoyaleSets();
            break;
        case 14:
            startBattle();
            break;
        case 15:
            clearBattle();
            break;
        case 16:
            g_menu.settingsPage = true;
            g_menu.row = 0;
            break;
        default:
            break;
        }
        clampCurrentSelection();
        return;
    }

    switch (row)
    {
    case 5:
        setManualSpawnForSelectedTeam();
        break;
    case 6:
        clearManualSpawnForSelectedTeam();
        break;
    case 11:
        addTeamSet();
        break;
    case 12:
        loadSelectedTeamSetIntoDraft(true);
        break;
    case 13:
        updateSelectedTeamSet();
        break;
    case 14:
        removeSelectedTeamSet();
        break;
    case 15:
        clearSelectedTeamSets();
        break;
    case 16:
        startBattle();
        break;
    case 17:
        clearBattle();
        break;
    case 18:
        g_menu.settingsPage = true;
        g_menu.row = 0;
        break;
    default:
        break;
    }
    clampCurrentSelection();
}

bool currentMenuLeftRightUsesRepeat()
{
    if (!g_menu.open)
        return false;

    if (g_menu.settingsPage)
        return (g_menu.row >= 5 && g_menu.row <= 12) || g_menu.row == 14;

    int row = logicalMenuRow(g_menu.row);
    if (freeForAllSelected())
        return row == 2 || row == 3 || row == 7 || row == 8;

    return row == 2 || row == 3 || row == 9 || row == 10;
}

void updateMenuInput()
{
    if (g_runtime.battleActive && !g_menu.open && keyPressed(kLeaderboardToggleKey))
    {
        toggleSpectatorCamera();
        return;
    }
    if (g_runtime.battleActive && g_runtime.spectatorCameraActive && !g_menu.open && keyPressed(VK_LEFT))
    {
        selectSpectatorCameraTarget(-1);
        return;
    }
    if (g_runtime.battleActive && g_runtime.spectatorCameraActive && !g_menu.open && keyPressed(VK_RIGHT))
    {
        selectSpectatorCameraTarget(1);
        return;
    }

    if (!g_runtime.leaderboardLines.empty() && keyPressed(kLeaderboardToggleKey))
    {
        toggleLeaderboardMode();
        return;
    }

    if (battlePreparationActive())
    {
        if (keyPressed(g_settings.menuKey))
            setStatus(g_runtime.status.empty() ? "Preparing battle" : g_runtime.status, 1500);
        return;
    }

    if (keyPressed(g_settings.menuKey))
    {
        if (!g_runtime.leaderboardLines.empty())
            clearLeaderboard();

        g_menu.open = !g_menu.open;
        setStatus(g_menu.open ? "Battle Creator opened" : "Battle Creator closed");
        return;
    }

    if (!g_menu.open)
        return;

    if (keyPressed(VK_UP))
    {
        --g_menu.row;
        if (g_menu.row < 0)
            g_menu.row = menuRowCount() - 1;
    }
    if (keyPressed(VK_DOWN))
    {
        ++g_menu.row;
        if (g_menu.row >= menuRowCount())
            g_menu.row = 0;
    }
    bool repeatLeftRight = currentMenuLeftRightUsesRepeat();
    if (repeatLeftRight ? keyRepeated(VK_LEFT) : keyPressed(VK_LEFT))
        adjustSelected(-1);
    if (repeatLeftRight ? keyRepeated(VK_RIGHT) : keyPressed(VK_RIGHT))
        adjustSelected(1);
    if (keyPressed(VK_RETURN) || keyPressed(VK_SPACE))
        activateSelected();
    if (keyPressed(VK_DELETE))
        clearBattle();
    if (keyPressed('R'))
    {
        loadSettings();
        clampAllRosterSlots();
        clampCurrentSelection();
        setStatus("Reloaded Battle Creator INIs", 5000);
    }
    if (!g_menu.settingsPage && keyPressed('N'))
        randomizeCurrentMode();
    if (!g_menu.settingsPage && !freeForAllSelected())
    {
        for (int i = 0; i < kTeamCount; ++i)
        {
            if (keyPressed(static_cast<DWORD>('1' + i)))
            {
                g_menu.team = i;
                g_menu.slot = 0;
                loadSelectedTeamSetIntoDraft(false);
                clampCurrentSelection();
            }
        }
    }
}

void mainLoop()
{
    loadSettings();
    std::srand(static_cast<unsigned int>(now()));

    while (true)
    {
        DWORD t = now();
        updateMenuInput();
        updateBattlePreparation();
        if (!battlePreparationActive())
            updateBattle();
        updateBattleCorpseCleanup(t);
        updatePlayerDeadEyeSuppression(t);
        updateSpectatorCamera(t);
        maintainPlayerVitalsRefill(t);

        if (g_menu.open && !battlePreparationActive())
            drawMenu();
        else
            drawCompactStatus();

        drawManualTeamSpawnMarkers();

        WAIT(0);
    }
}
}

void ScriptMain()
{
    mainLoop();
}

BOOL APIENTRY DllMain(HMODULE module, DWORD reason, LPVOID)
{
    switch (reason)
    {
    case DLL_PROCESS_ATTACH:
        scriptRegister(module, ScriptMain);
        break;
    case DLL_PROCESS_DETACH:
        deleteFighters();
        removeRelationshipGroups();
        scriptUnregister(module);
        break;
    }

    return TRUE;
}

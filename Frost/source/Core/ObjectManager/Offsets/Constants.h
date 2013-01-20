/*	Frost Open-Source World of Warcraft Bot
	Copyright (C) 2013 https://code.google.com/p/ejt-projects/

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>. */

#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_

/* 
// From Ownedcore
// http://www.ownedcore.com/forums/world-of-warcraft/world-of-warcraft-bots-programs/wow-memory-editing/257771-wow-constant-data-enums-structs-etc.html
*/
	
namespace Constants {
	namespace Shapeshift {
		enum Form {
			Normal = 0,
			Cat = 1,
			TreeOfLife = 2,
			Travel = 3,
			Aqua = 4,
			Bear = 5,
			Ambient = 6,
			Ghoul = 7,
			DireBear = 8,
			CreatureBear = 14,
			CreatureCat = 15,
			GhostWolf = 16,
			BattleStance = 17,
			DefensiveStance = 18,
			BerserkerStance = 19,
			EpicFlightForm = 27,
			Shadow = 28,
			Stealth = 30,
			Moonkin = 31,
			SpiritOfRedemption = 32
		};
	}

	namespace Stand {
		enum State {
			Stand = 0,
			Sit = 1,
			SittingInChair = 2,
			Sleeping = 3,
			SittingInLowChair = 4,
			SittingInMediumChair = 5,
			SittingInHighChair = 6,
			Dead = 7,
			Kneeling = 8,
			Type9 = 9,
		};
	}

	namespace PvP {
		enum State {
			None = 0,
			PVP = 0x1,
			FFAPVP = 0x4,
			InPvPSanctuary = 0x8,
		};
	}

	namespace WoWItem {
			enum Type {
			Consumable,
			Container,
			Weapon,
			Gem,
			Armor,
			Reagent,
			Projectile,
			TradeGoods,
			Generic,
			Recipe,
			Money,
			Quiver,
			QUest,
			Key,
			Permanent,
			Misc
		};
	}
	
	namespace WoWPower {
		enum Type {
			Mana,
			Rage,
			Focus,
			Energy,
			Happiness,
			RunicPower,
			Runes,
			Health,
			UNKNOWN
		};
	}
	
	namespace WoWObjectType {
		enum Flag {
			Object = 0x1,
			Item = 0x2,
			Container = 0x4,
			Unit = 0x8,
			Player = 0x10,
			GameObject = 0x20,
			DynamicObject = 0x40,
			Corpse = 0x80,
			AiGroup = 0x100,
			AreaTrigger = 0x200,
		};
	}
	
	namespace WoWObject {
		enum Type {
			Object = 0,
			Item = 1,
			Container = 2,
			Unit = 3,
			Player = 4,
			GameObject = 5,
			DynamicObject = 6,
			Corpse = 7,
			AiGroup = 8,
			AreaTrigger = 9
		};
	}
	
	namespace WoWGameObject {
		enum Type {
			Door = 0,
			Button = 1,
			QuestGiver = 2,
			Chest = 3,
			Binder = 4,
			Generic = 5,
			Trap = 6,
			Chair = 7,
			SpellFocus = 8,
			Text = 9,
			Goober = 0xa,
			Transport = 0xb,
			AreaDamage = 0xc,
			Camera = 0xd,
			WorldObj = 0xe,
			MapObjTransport = 0xf,
			DuelArbiter = 0x10,
			FishingNode = 0x11,
			Ritual = 0x12,
			Mailbox = 0x13,
			AuctionHouse = 0x14,
			SpellCaster = 0x16,
			MeetingStone = 0x17,
			Unkown18 = 0x18,
			FishingPool = 0x19,
			FORCEDWORD = 0xFFFFFFFF,
		};
	}
	
	namespace WoWEquip {
		enum WoWEquipSlot {
			Head = 0,
			Neck,
			Shoulders,
			Body,
			Chest,
			Waist,
			Legs,
			Feet,
			Wrists,
			Hands,
			Finger1,
			Finger2,
			Trinket1,
			Trinket2,
			Back,
			MainHand,
			OffHand,
			Ranged,
			Tabard
		};
	}
	
	namespace WoWClass {
		enum Names {
			None = 0,
			Warrior = 1,
			Paladin = 2,
			Hunter = 3,
			Rogue = 4,
			Priest = 5,
			DeathKnight = 6,
			Shaman = 7,
			Mage = 8,
			Warlock = 9,
			Druid = 11,
		};
	}
	
	namespace WoWClassification {
		enum Names {
			Normal = 0,
			Elite = 1,
			RareElite = 2,
			WorldBoss = 3,
			Rare = 4
		};
	}
	
	namespace WoWRace {
		enum Names {
			Human = 1,
			Orc,
			Dwarf,
			NightElf,
			Undead,
			Tauren,
			Gnome,
			Troll,
			Goblin,
			BloodElf,
			Draenei,
			FelOrc,
			Naga,
			Broken,
			Skeleton = 15,
		};
	}
	
	namespace WoWCreature {
		enum Type {
			Unknown = 0,
			Beast,
			Dragon,
			Demon,
			Elemental,
			Giant,
			Undead,
			Humanoid,
			Critter,
			Mechanical,
			NotSpecified,
			Totem,
			NonCombatPet,
			GasCloud
		};
	}
	
	namespace WoWGender {
		enum Names {
			Male,
			Female,
			Unknown
		};
	}
	
	namespace WoWUnit {
		enum Relation {
			Hated = 0,
			Hostile = 1,
			Unfriendly = 2,
			Neutral = 3,
			Friendly = 4,
		};
	}
	
	namespace WoWDispel {
		enum Type {
			None = 0,
			Magic = 1,
			Curse = 2,
			Disease = 3,
			Poison = 4,
			Stealth = 5,
			Invisibility = 6,
			All = 7,
			//Special_NpcOnly=8,
			Enrage = 9,
			//ZgTrinkets=10
		};
	}
	
	namespace WoWQuest {
		enum Type {
			Group = 1,
			Life = 21,
			PvP = 41,
			Raid = 62,
			Dungeon = 81,
			WorldEvent = 82,
			Legendary = 83,
			Escort = 84,
			Heroic = 85,
			Raid_10 = 88,
			Raid_25 = 89,
		};
	}
	
	namespace Sheath {
		enum Type {
			Undetermined = -1,
			None = 0,
			Melee = 1,
			Ranged = 2,

			Shield = 4,
			Rod = 5,
			Light = 7
		};
	}

    /// <summary>
    /// The direction of movement in WoW as per the CGInputControl_ToggleControlBit function.
    /// These are actually the flags that are set/unset!
    /// </summary>
	namespace MovementDirection {
		enum Flags {
			None = 0,
			RMouse = (1 << 0), // 0x1,
			LMouse = (1 << 1), // 0x2,
			// 2 and 3 not used apparently. Possibly for flag masking?
			Forward = (1 << 4), // 0x10,
			Backward = (1 << 5), // 0x20,
			StrafeLeft = (1 << 6), // 0x40,
			StrafeRight = (1 << 7), // 0x80,
			TurnLeft = (1 << 8), // 0x100,
			TurnRight = (1 << 9), // 0x200,
			PitchUp = (1 << 10), // 0x400, For flying/swimming
			PitchDown = (1 << 11), // 0x800, For flying/swimming
			AutoRun = (1 << 12), // 0x1000,
			JumpAscend = (1 << 13), // 0x2000, For flying/swimming
			Descend = (1 << 14), // 0x4000, For flying/swimming

			ClickToMove = (1 << 22), // 0x400000, Note: Only turns the CTM flag on or off. Has no effect on movement!

			// 25 used somewhere. Can't figure out what for. Checked in Lua_IsMouseTurning. Possible camera turn?
			// Or mouse input flag? (Flag used: 0x2000001)
		};
	}
		
	namespace Movement {
		enum Flags {
			Forward = 0x1,
			Backward = 0x2,
			StrafeLeft = 0x4,
			StrafeRight = 0x8,

			StrafeMask=StrafeLeft|StrafeRight,

			Left = 0x10,
			Right = 0x20,

			TurnMask=Left|Right,

			MoveMask=Forward|Backward|StrafeMask|TurnMask,

			PitchUp = 0x40,
			PitchDown = 0x80,
			Walk = 0x100,
			TimeValid = 0x200,
			Immobilized = 0x400,
			DontCollide = 0x800,
			// JUMPING
			Redirected = 0x1000,
			Rooted = 0x2000,
			Falling = 0x4000,
			FallenFar = 0x8000,
			PendingStop = 0x10000,
			Pendingunstrafe = 0x20000,
			Pendingfall = 0x40000,
			Pendingforward = 0x80000,
			PendingBackward = 0x100000,
			PendingStrafeLeft = 0x200000,
			PendingStrafeRght = 0x400000,
			PendMoveMask = 0x180000,
			PendStrafeMask = 0x600000,
			PendingMask = 0x7f0000,
			Moved = 0x800000,
			Sliding = 0x1000000,
			Swimming = 0x2000000,
			SplineMover = 0x4000000,
			SpeedDirty = 0x8000000,
			Halted = 0x10000000,
			Nudge = 0x20000000,

			FallMask = 0x100c000,
			Local = 0x500f400,
			PitchMask = 0xc0,
			MotionMask = 0xff,
			StoppedMask = 0x3100f,
		};
	}
	
	namespace State {
		enum Flag {
			None = 0,
			AlwaysStand = 0x1,
			Sneaking = 0x2,
			UnTrackable = 0x4,
		};
	}
	
	namespace UnitDynamic {
		enum Flags {
			None = 0,
			Lootable = 0x1,
			TrackUnit = 0x2,
			TaggedByOther = 0x4,
			TaggedByMe = 0x8,
			SpecialInfo = 0x10,
			Dead = 0x20,
			ReferAFriendLinked = 0x40,
			IsTappedByAllThreatList = 0x80,
		};
	}
	
	namespace Unit {
		enum Flags {
			None = 0,
			Sitting = 0x1,
			//SelectableNotAttackable_1 = 0x2,
			Influenced = 0x4, // Stops movement packets
			PlayerControlled = 0x8, // 2.4.2
			Totem = 0x10,
			Preparation = 0x20, // 3.0.3
			PlusMob = 0x40, // 3.0.2
			//SelectableNotAttackable_2 = 0x80,
			NotAttackable = 0x100,
			//Flag_0x200 = 0x200,
			Looting = 0x400,
			PetInCombat = 0x800, // 3.0.2
			PvPFlagged = 0x1000,
			Silenced = 0x2000, //3.0.3
			//Flag_14_0x4000 = 0x4000,
			//Flag_15_0x8000 = 0x8000,
			//SelectableNotAttackable_3 = 0x10000,
			Pacified = 0x20000, //3.0.3
			Stunned = 0x40000,
			CanPerformAction_Mask1 = 0x60000,
			Combat = 0x80000, // 3.1.1
			TaxiFlight = 0x100000, // 3.1.1
			Disarmed = 0x200000, // 3.1.1
			Confused = 0x400000, //  3.0.3
			Fleeing = 0x800000,
			Possessed = 0x1000000, // 3.1.1
			NotSelectable = 0x2000000,
			Skinnable = 0x4000000,
			Mounted = 0x8000000,
			//Flag_28_0x10000000 = 0x10000000,
			Dazed = 0x20000000,
			Sheathe = 0x40000000,
			//Flag_31_0x80000000 = 0x80000000,
		};

		enum Flags2 {
			FeignDeath = 0x1,
			NoModel = 0x2,
			Flag_0x4 = 0x4,
			Flag_0x8 = 0x8,
			Flag_0x10 = 0x10,
			Flag_0x20 = 0x20,
			ForceAutoRunForward = 0x40,

			/// <summary>
			/// Treat as disarmed?
			/// Treat main and off hand weapons as not being equipped?
			/// </summary>
			Flag_0x80 = 0x80,

			/// <summary>
			/// Skip checks on ranged weapon?
			/// Treat it as not being equipped?
			/// </summary>
			Flag_0x400 = 0x400,

			Flag_0x800 = 0x800,
			Flag_0x1000 = 0x1000,
		};

		enum NPCFlags {
			UNIT_NPC_FLAG_NONE = 0x00000000,
			UNIT_NPC_FLAG_GOSSIP = 0x00000001, // 100%
			UNIT_NPC_FLAG_QUESTGIVER = 0x00000002, // guessed, probably ok
			UNIT_NPC_FLAG_UNK1 = 0x00000004,
			UNIT_NPC_FLAG_UNK2 = 0x00000008,
			UNIT_NPC_FLAG_TRAINER = 0x00000010, // 100%
			UNIT_NPC_FLAG_TRAINER_CLASS = 0x00000020, // 100%
			UNIT_NPC_FLAG_TRAINER_PROFESSION = 0x00000040, // 100%
			UNIT_NPC_FLAG_VENDOR = 0x00000080, // 100%
			UNIT_NPC_FLAG_VENDOR_AMMO = 0x00000100, // 100%, general goods vendor
			UNIT_NPC_FLAG_VENDOR_FOOD = 0x00000200, // 100%
			UNIT_NPC_FLAG_VENDOR_POISON = 0x00000400, // guessed
			UNIT_NPC_FLAG_VENDOR_REAGENT = 0x00000800, // 100%
			UNIT_NPC_FLAG_REPAIR = 0x00001000, // 100%
			UNIT_NPC_FLAG_FLIGHTMASTER = 0x00002000, // 100%
			UNIT_NPC_FLAG_SPIRITHEALER = 0x00004000, // guessed
			UNIT_NPC_FLAG_SPIRITGUIDE = 0x00008000, // guessed
			UNIT_NPC_FLAG_INNKEEPER = 0x00010000, // 100%
			UNIT_NPC_FLAG_BANKER = 0x00020000, // 100%
			UNIT_NPC_FLAG_PETITIONER = 0x00040000, // 100% 0xC0000 = guild petitions, 0x40000 = arena team petitions
			UNIT_NPC_FLAG_TABARDDESIGNER = 0x00080000, // 100%
			UNIT_NPC_FLAG_BATTLEMASTER = 0x00100000, // 100%
			UNIT_NPC_FLAG_AUCTIONEER = 0x00200000, // 100%
			UNIT_NPC_FLAG_STABLEMASTER = 0x00400000, // 100%
			UNIT_NPC_FLAG_GUILD_BANKER = 0x00800000, // cause client to send 997 opcode
			UNIT_NPC_FLAG_SPELLCLICK = 0x01000000, // cause client to send 1015 opcode (spell click)
			UNIT_NPC_FLAG_GUARD = 0x10000000, // custom flag for guards
		};
	}
	
	namespace GameObject {
		enum Flags {
			/// <summary>
			/// 0x1
			/// Disables interaction while animated
			/// </summary>
			InUse = 0x01,
			/// <summary>
			/// 0x2
			/// Requires a key, spell, event, etc to be opened. 
			/// Makes "Locked" appear in tooltip
			/// </summary>
			Locked = 0x02,
			/// <summary>
			/// 0x4
			/// Objects that require a condition to be met before they are usable
			/// </summary>
			ConditionalInteraction = 0x04,
			/// <summary>
			/// 0x8
			/// any kind of transport? Object can transport (elevator, boat, car)
			/// </summary>
			Transport = 0x08,
			GOFlag_0x10 = 0x10,
			/// <summary>
			/// 0x20
			/// These objects never de-spawn, but typically just change state in response to an event
			/// Ex: doors
			/// </summary>
			DoesNotDespawn = 0x20,
			/// <summary>
			/// 0x40
			/// Typically, summoned objects. Triggered by spell or other events
			/// </summary>
			Triggered = 0x40,

			GOFlag_0x80 = 0x80,
			GOFlag_0x100 = 0x100,
			GOFlag_0x200 = 0x200,
			GOFlag_0x400 = 0x400,
			GOFlag_0x800 = 0x800,
			GOFlag_0x1000 = 0x1000,
			GOFlag_0x2000 = 0x2000,
			GOFlag_0x4000 = 0x4000,
			GOFlag_0x8000 = 0x8000,

			Flag_0x10000 = 0x10000,
			Flag_0x20000 = 0x20000,
			Flag_0x40000 = 0x40000,
		};
	}
	
	namespace Corpse {
		enum Flags {
			CORPSE_FLAG_NONE = 0x00,
			CORPSE_FLAG_BONES = 0x01,
			CORPSE_FLAG_UNK1 = 0x02,
			CORPSE_FLAG_UNK2 = 0x04,
			CORPSE_FLAG_HIDE_HELM = 0x08,
			CORPSE_FLAG_HIDE_CLOAK = 0x10,
			CORPSE_FLAG_LOOTABLE = 0x20
		};
	}
}

#endif
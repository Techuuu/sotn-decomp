#include "common.h"
#include "dra.h"
#include "objects.h"
#include "sfx.h"

void func_80113AAC(void) {
    s32 var_s1 = 0;
    s32 temp;

    g_Player.unk4A++;
    if (func_8010FDF8(2) != 0) {
        return;
    }

    switch (PLAYER.step_s) {
    case 0:
        if (g_Player.pl_vram_flag & 2) {
            func_801139CC(3);
            if (g_Player.unk4A >= 5) {
                PLAYER.step_s = 2;
                PLAYER.unk1E = 0x800;
                PLAYER.unk22 = 2;
                PLAYER.unk20 = 0;
                PLAYER.unk19 |= 4;
                PLAYER.facing = (PLAYER.facing + 1) & 1;
                func_8010DA48(0x2B);
            } else {
                PLAYER.step_s = 3;
            }
        } else if (g_Player.unk4A > 28) {
            PLAYER.step_s = 1;
            PLAYER.accelerationY = -0x60000;
            func_8010DA48(0x1B);
        }
        break;

    case 1:
        if (g_Player.pl_vram_flag & 2) {
            PLAYER.step_s = 2;
            func_801139CC(3);
        } else {
            PLAYER.accelerationY += 0x6000;
            if (PLAYER.accelerationY > 0x8000) {
                var_s1 = 1;
            }
        }
        break;

    case 2:
        PLAYER.unk19 |= 4;
        PLAYER.unk20 = 0;
        PLAYER.unk22 = 2;
        if (g_Player.unk4A >= 0x39) {
            func_8010DA48(0x2D);
            PLAYER.unk1E = 0;
            PLAYER.step_s = 4;
            PLAYER.unk19 &= 0xFB;
            PLAYER.facing = (PLAYER.facing + 1) & 1;
        }
        break;

    case 3:
        if (g_Player.unk4A > 20) {
            var_s1 = 1;
        }
        break;

    case 4:
        PLAYER.accelerationY += 0x1000;
        if (PLAYER.animFrameDuration < 0) {
            var_s1 = 2;
        }
        break;
    }

    if (var_s1 != 0) {
        temp = 0; // TODO: !FAKE
        if ((var_s1 - 1) != temp) {
            func_8010DA48(0x1C);
        }
        PLAYER.palette = 0x8100;
        PLAYER.step_s = 1;
        PLAYER.step = Player_Jump;
    }
}

s32 func_80113D7C(s16 arg0) {
    s32 sp10[3];
    s32 sfx;
    s32 temp_s0 = func_800FE97C(&sp10[0], 2, arg0 / 2, 1);
    s16 step;
    u16 temp_s1;

    func_80118C84(sp10[2], 0);
    func_800FE8F0();
    if (temp_s0 != 4) {
        g_Player.D_80072F04 = 4;
        g_Player.unk40 = 0x8166;
        sfx = D_800ACF8A[(rand() & 1)];
        PlaySfx(sfx);
        if (step && step) // TODO: !FAKE
            ;
        return 0;
    }
    step = PLAYER.step;
    temp_s1 = PLAYER.step_s;
    sp10[0] = 0;
    sp10[1] = 0;
    SetPlayerStep(Player_Unk16);
    func_80115394(&sp10[0], step, temp_s1);
    return -1;
}

s32 func_80113E68(void) {
    s16 rnd = rand();
    PLAYER.ext.generic.unkAC = 0x2E + (rnd % 3);
    return rnd % 16;
}

void func_80113EE0(void) {
    PLAYER.animSet = 1;
    PLAYER.unk19 &= 0xF3;
    PLAYER.animFrameDuration = 0;
    PLAYER.animFrameIdx = 0;
    PLAYER.objectId = 0;
    PLAYER.blendMode = 0;
    g_Player.unk44 = 0;
    g_Player.unk46 = 0;
    PLAYER.unk1E = 0;
    PLAYER.zPriority = g_zEntityCenter.S16.unk0;
    if (g_Entities[UNK_ENTITY_10].objectId == 0x22) {
        func_8010FAF4();
    }
}

void func_80113F7C(void) {
    Entity* entity = PLAYER.ext.generic.unkB8.entityPtr;
    s16 posX;
    s32 var_a0;
    s32 var_a2;

    if (entity->facing != 0) {
        var_a2 = -entity->unk10;
    } else {
        var_a2 = entity->unk10;
    }

    if (PLAYER.facing != 0) {
        var_a0 = -PLAYER.unk10;
    } else {
        var_a0 = PLAYER.unk10;
    }

    posX = var_a0 + PLAYER.posX.i.hi - entity->posX.i.hi - var_a2;

    if (ABS(posX) < 16) {
        if (entity->accelerationX != 0) {
            if (entity->accelerationX >= 0) {
                PLAYER.objectRoomIndex = 1;
                return;
            }
            goto block_14;
        }
        goto block_13;
    }
    // TODO: labels are !FAKE
block_13:
    if (posX < 0) {
    block_14:
        PLAYER.objectRoomIndex = 0;
        return;
    }

    PLAYER.objectRoomIndex = 1;
}

void AccelerateX(s32);
void PlaySfx(int);
void func_8010DA48(u32);
void func_8010E1EC(s32 speed);
void func_8010E3B8(s32 accelerationX);
void func_8010E7AC(void);
s32 func_8010FDF8(s32);
void func_801139CC(s32);
extern void (*D_8017A010)(void);
extern s32 D_80072CF0[]; // part of g_Player.D_80072BD0
extern s16 D_800ACF84[];

typedef struct {
    u32 unk0;
    u32 unk4; // dam_kind or damageKind
    u32 unk8;
} UnkPlayerEntityStruct;
// #ifndef NON_MATCHING
// INCLUDE_ASM("asm/us/dra/nonmatchings/73AAC", func_8011405C);
// #else

// Function responsible of how Alucard handles the damage received
void func_8011405C(UnkPlayerEntityStruct* arg0, s16 arg1, s16 arg2) {
    s32 i;
    s32 var_a3;
    s32 var_s0;
    s32 var_s0_3;
    s32 var_s3;
    s32 var_s4;

    var_s4 = 0;
    switch (PLAYER.step_s) { /* switch 1 */
    case 0:                  /* switch 1 */
        var_s4 = 1;
        func_80113EE0();
        if (arg0->unk4 < 0x10) {
            func_80113F7C();
        } else {
            if (arg0->unk4 == 0x10) {
                func_80113F7C();
            }
            if (arg0->unk4 == 0x11) {
                PLAYER.objectRoomIndex = 1;
            }
            if (arg0->unk4 == 0x12) {
                PLAYER.objectRoomIndex = 0;
            }
        }
        if (g_Player.unk0C & 0x01000000) {
            PLAYER.accelerationY = -0x30000;
            func_8010E3B8(-0x14000);
            PLAYER.step = 0x2B;
            PLAYER.step_s = 0;
            PLAYER.ext.generic.unkAC = 0xD1;
            PlaySfx(0x6ED);
            func_8011AAFC(g_CurrentEntity, 0x55, 0);
            D_8017A010();
            if (g_Player.unk72 != 0) {
                PLAYER.accelerationY = 0;
            }
            return;
        }
        var_s0 = 0;
        func_80111CC0();
        var_s3 = 0;
        switch (arg0->unk4) { /* switch 2 */
        case 5:               /* switch 2 */
            var_s0 = 13;
            g_Player.unk5A = arg0->unk8;
            /* fallthrough */
        case 4: /* switch 2 */
            PLAYER.posY.val--;
            PLAYER.accelerationY = -0x8000;
            func_8010E3B8(-0x80000);
            PLAYER.step_s = var_s0 + 2;
            PLAYER.ext.generic.unkAC = 0x2E;
            g_Player.D_80072F04 = 0x200;
            PLAYER.facing = PLAYER.objectRoomIndex;
            if (arg0->unk4 == 4) {
                var_s3 = (rand() & 1) + 1;
            }
            break;
        case 16: /* switch 2 */
        case 17: /* switch 2 */
        case 18: /* switch 2 */
            var_s3 = (rand() & 1) + 3;
            switch (arg1) {
            case 0:
            case 1:
                break;
            case 3:
            case 4:
                var_s0 = 0x10000;
                break;
            }
            PLAYER.accelerationY = var_s0 + -0x40000;
            func_8010E3B8(-0x1AAAA);
            PLAYER.step_s = 1;
            if (func_80113E68() == 0) {
                PLAYER.ext.generic.unkAC = 0x40;
            }
            break;
        case 3: /* switch 2 */
        case 7: /* switch 2 */
            var_s3 = (rand() & 1) + 3;
            switch (arg1) { /* switch 3 */
            case 3:         /* switch 3 */
            case 4:         /* switch 3 */
                PLAYER.accelerationY = -0x30000;
                func_8010E3B8(-0x1AAAA);
                PLAYER.step_s = 1;
                if (func_80113E68() == 0) {
                    PLAYER.ext.generic.unkAC = 0x40;
                }
                break;
            case 2: /* switch 3 */
            case 6: /* switch 3 */
                PLAYER.accelerationY = 0;
                func_8010E3B8(-0x28000);
                PLAYER.step_s = 7;
                PLAYER.ext.generic.unkAC = 0x23;
                func_8011AAFC(g_CurrentEntity, 0, 0);
                break;
            default: /* switch 3 */
                PLAYER.accelerationY = var_s0 + -0x40000;
                func_8010E3B8(-0x1AAAA);
                PLAYER.step_s = 1;
                if (func_80113E68() == 0) {
                    PLAYER.ext.generic.unkAC = 0x40;
                }
                break;
            }
            break;
        case 2: /* switch 2 */
            var_s3 = (rand() & 1) + 5;
            switch (arg1) { /* switch 4 */
            case 0:         /* switch 4 */
            case 1:         /* switch 4 */
                PLAYER.accelerationY = 0;
                func_8010E3B8(-0x28000);
                PLAYER.step_s = 6;
                var_a3 = rand() & 1;
                if (PLAYER.objectRoomIndex != PLAYER.facing) {
                    var_a3 |= 2;
                }
                PLAYER.ext.generic.unkAC = var_a3 + 0x31;
                func_8011AAFC(g_CurrentEntity, 0x60000, 0);
                break;
            case 2: /* switch 4 */
            case 6: /* switch 4 */
                PLAYER.accelerationY = 0;
                func_8010E3B8(-0x28000);
                PLAYER.step_s = 7;
                PLAYER.ext.generic.unkAC = 0x23;
                func_8011AAFC(g_CurrentEntity, 0, 0);
                break;
            default: /* switch 4 */
                PLAYER.accelerationY = -0x20000;
                func_8010E3B8(-0x14000);
                PLAYER.step_s = 1;
                func_80113E68();
                break;
            }
            break;
        default: /* switch 2 */
            FntPrint("dam_kind:%04x\n", arg0->unk4);
            break;
        }

        g_Player.unk40 = 0x8166;
        g_Player.D_80072F04 = 6;
        PlaySfx(D_800ACF84[var_s3]);
        if (arg0->unk0 & 0x100) { // cursed
            g_Player.D_80072F02 = func_800FDB18(1, 0x400);
            g_Player.unk40 = 0x8165;
            func_8011AAFC(g_CurrentEntity, 0x2002F, 0);
            func_8011AAFC(g_CurrentEntity, 0x17002C, 0);
            PlaySfx(0x6F2);
            break;
        }
        if (arg0->unk0 & 0x80) { // poison
            g_Player.D_80072F00 = func_800FDB18(0, 0xFFF);
            g_Player.unk40 = 0x8164;
            func_8011AAFC(g_CurrentEntity, 0x16002C, 0);
            func_8011AAFC(g_CurrentEntity, 0x1002F, 0);
            PlaySfx(0x6F2);
            break;
        }
        if (arg0->unk0 & 0x8000) {
            PlaySfx(0x690);
            func_8011AAFC(g_CurrentEntity, 0x45002C, 0);
            g_Player.unk40 = 0x8160;
            if (arg0->unk0 & 0x10000) {
                func_8011AAFC(g_CurrentEntity, 0x13, 0);
                g_Player.D_80072F04 = 0xA;
            } else {
                func_8011AAFC(g_CurrentEntity, 0x10011, 0);
                func_8011AAFC(g_CurrentEntity, 0x12, 0);
                g_Player.D_80072F04 = 0x10;
            }
            break;
        }
        if (arg0->unk0 & 0x4000) {
            func_8011AAFC(g_CurrentEntity, 0x2D, 0);
            func_8011AAFC(g_CurrentEntity, 0x46002C, 0);
            g_Player.D_80072F04 = 0x18;
            g_Player.unk40 = 0x8102;
        } else if (arg0->unk0 & 0x2000) {
            func_8011AAFC(g_CurrentEntity, 0x2E, 0);
            g_Player.D_80072F04 = 0xC;
            g_Player.unk40 = 0x8169;
            PLAYER.ext.generic.unkAC = 0x2E;
        } else {
            if (arg0->unk0 & 0x1000) {
                func_8011AAFC(g_CurrentEntity, 0x77, 0);
                func_8011AAFC(g_CurrentEntity, 0x68002C, 0);
                g_Player.D_80072F04 = 8;
                g_Player.unk40 = 0x8168;
            }
            if (arg0->unk0 & 0x800) {
                func_8011AAFC(g_CurrentEntity, 0x71, 0);
                func_8011AAFC(g_CurrentEntity, 0x62002C, 0);
                g_Player.D_80072F04 = 0x10;
                g_Player.unk40 = 0x8164;
            }
            if (arg0->unk0 & 0x40) {
                PlaySfx(0x62E);
                g_Player.unk40 = 0x8166;
                func_8011AAFC(g_CurrentEntity, 0x42002C, 0);
                if (arg0->unk0 & 0x10000) {
                    func_8011AAFC(g_CurrentEntity, 0x50015, 0);
                    g_Player.D_80072F04 = 0xA;
                } else {
                    func_8011AAFC(g_CurrentEntity, 0x50014, 0);
                    g_Player.D_80072F04 = 0x10;
                }
                break;
            } else if (!(arg0->unk0 & 0xFAC0)) {
                func_8011AAFC(g_CurrentEntity, 0x58002C, 0);
            }
        }
        break;
    case 1: /* switch 1 */
        if (func_8010FDF8(0x20280) != 0) {
            return;
        }
        if (PLAYER.animFrameDuration < 0) {
            func_8010DA48(0x1C);
            PLAYER.facing = (PLAYER.facing + 1) & 1;
        }
        break;
        break;
    case 2:  /* switch 1 */
    case 15: /* switch 1 */
        if (!(g_Player.unk04 & 0x8000) || (g_Player.pl_vram_flag & 0x8000)) {
            if ((g_Player.pl_vram_flag & 0x8000) && !(D_8003C8C4 & 1)) {
                func_8011AAFC(g_CurrentEntity, 0xA0045, 0);
            }
            if (!(g_Player.pl_vram_flag & 0xE)) {
                break;
            }
            if (g_Player.pl_vram_flag & 2) {
                func_801139CC(1);
                PLAYER.accelerationX /= 2;
                PLAYER.accelerationY = 0;
                g_Player.D_80072F10 = 0x18;
                PLAYER.step_s = 5;
                if (g_Player.unk52 == 15 &&
                    func_80113D7C(g_Player.unk5A) != 0) {
                    return;
                }
                break;
            }
            if (g_StageId != STAGE_BO6 && g_StageId != STAGE_RBO6 &&
                g_StageId != STAGE_DRE) {
                for (i = 2; i < 7; i++) {
                    if (g_Player.D_80072CF0[i][0] & 2) {
                        break;
                    }
                }
                if (i == 7) {
                    for (i = 9; i < 14; i++) {
                        if (g_Player.D_80072CF0[i][0] & 2) {
                            break;
                        }
                    }
                }
                if (i == 14) {
                    goto block_89;
                }
            }
            if (PLAYER.step_s == 15) {
                PLAYER.accelerationY = -0x28000;
                g_Player.D_80072F10 = 8;
                func_8010DA48(0x3F);
                PlaySfx(0x644);
                PLAYER.step_s = 3;
                func_80102CD8(2);
                func_8011AAFC(g_CurrentEntity, 0x8001F, 0);
                if (func_80113D7C(g_Player.unk5A) != 0) {
                    return;
                }
            } else {
                PLAYER.accelerationY = 0;
                g_Player.D_80072F10 = 0x30;
                PLAYER.accelerationX /= 2;
                PlaySfx(0x647);
                PLAYER.unk1E = 0x400;
                PLAYER.unk20 = 0x10;
                PLAYER.unk22 = 4;
                PLAYER.unk19 |= 4;
                func_8010DA48(0x2C);
                PLAYER.step_s = 0xE;
                func_8011AAFC(g_CurrentEntity, 0x8001F, 0);
            }
            break;
        }
    block_89:
        PLAYER.accelerationY = -0x40000;
        func_8010E3B8(-0x14000);
        PLAYER.ext.generic.unkAC = 0x2F;
        if (PLAYER.accelerationX != 0) {
            var_s0_3 = 3;
        } else {
            var_s0_3 = -3;
        }
        PLAYER.posY.i.hi += 0x15;
        PLAYER.posX.i.hi += var_s0_3;
        func_8011AAFC(g_CurrentEntity, 0x90004, 0);
        PLAYER.posY.i.hi -= 0x15;
        PLAYER.posX.i.hi -= var_s0_3;
        PlaySfx(0x644);
        func_80102CD8(2);
        PLAYER.step_s = 1;
        if (g_Player.unk52 == 0xF && func_80113D7C(g_Player.unk5A) != 0) {
            return;
        }
        break;
    case 3: /* switch 1 */
        if (g_Player.D_80072F10 == 0) {
            AccelerateX(0xC000);
            if (func_8010FDF8(0x20280) != 0) {
                return;
            }
        }
        break;
    case 5: /* switch 1 */
        func_8010E1EC(0x2000);
        if (g_Player.D_80072F10 != 0) {
            if ((g_Player.pl_vram_flag & 2) && !(D_8003C8C4 & 3)) {
                func_801139CC(0);
            }
        } else if (g_Player.pl_vram_flag & 0xC) {
            if (!(g_Player.pl_vram_flag & 0xFF03)) {
                PLAYER.accelerationY += 0x1800;
                if (PLAYER.accelerationY > 0x70000) {
                    PLAYER.accelerationY = 0x70000;
                }
                if (!(D_8003C8C4 & 3)) {
                    func_8011AAFC(g_CurrentEntity, 0x4000C, 0);
                    break;
                }
            } else {
                PLAYER.step_s = 1;
                func_80113E68();
                PLAYER.animFrameIdx = 0;
                PLAYER.animFrameDuration = 0;
            }
        }
        break;
    case 14: /* switch 1 */
        PLAYER.unk19 |= 4;
        if (g_Player.D_80072F10 <= 0) {
            PLAYER.unk19 = PLAYER.unk19 & ~4;
            PLAYER.unk1E = 0x800;
            PLAYER.accelerationY = 0;
            PLAYER.accelerationX /= -2;
            func_8010DA48(0x1C);
            PLAYER.step_s = 1;
            PLAYER.step = 4;
            g_Player.unk44 = 0;
        }
        break;
    case 6: /* switch 1 */
    case 7: /* switch 1 */
        func_8010E1EC(0x2000);
        if (!(g_Player.pl_vram_flag & 1)) {
            func_8010E7AC();
        }
        if (PLAYER.animFrameDuration < 0) {
            if (PLAYER.step_s == 6) {
                func_8010E570(0);
            } else {
                func_8010E470(0, PLAYER.accelerationX);
            }
        }
        break;
    }
    if (var_s4 != 0 && g_Player.unk72 != 0) {
        PLAYER.accelerationY = 0;
    }
}
// #endif

INCLUDE_ASM("asm/us/dra/nonmatchings/73AAC", func_80114DF4);

INCLUDE_ASM("asm/us/dra/nonmatchings/73AAC", func_80115394);

void func_80115BB0(void) {
    PLAYER.unk19 = 4;
    PLAYER.accelerationY = 0;
    PLAYER.accelerationX = 0;
    PLAYER.animFrameDuration = 4;

    if (D_80097420[0] == 0) {
        if (g_Player.pl_vram_flag & 1) {
            func_8010E570(0);
        } else {
            func_8010E7AC();
        }
        func_8011AAFC(g_CurrentEntity, 0x4A0000 | 0x2C, 0);
        D_80097D37 = 0;
    }
}

// same as RIC/func_8015BB80
void func_80115C50(void) {
    s32 dist;

    if (g_StageId == STAGE_TOP) {
        dist = (g_CurrentRoom.left * 256) + playerX;
        dist = ABS(dist);

        if (dist - 8000 > 0) {
            PLAYER.posX.i.hi--;
        }

        dist = (g_CurrentRoom.left * 256) + playerX;
        dist = ABS(dist);

        if (dist - 8000 < 0) {
            PLAYER.posX.i.hi++;
        }
    }

    if (g_StageId == (STAGE_TOP | STAGE_INVERTEDCASTLE_FLAG)) {
        dist = (g_CurrentRoom.left * 256) + playerX;
        dist = ABS(dist);

        if (dist - 8384 > 0) {
            PLAYER.posX.i.hi--;
        }

        dist = (g_CurrentRoom.left * 256) + playerX;
        dist = ABS(dist);

        if (dist - 8384 < 0) {
            PLAYER.posX.i.hi++;
        }
    }
}

/*
 * Copyright 2013-2016, iH8sn0w. <iH8sn0w@iH8sn0w.com>
 *
 * This file is part of iBoot32Patcher.
 *
 * iBoot32Patcher is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * iBoot32Patcher is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with iBoot32Patcher.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <include/finders.h>
#include <include/functions.h>
#include <include/patchers.h>
#include <include/iBoot32Patcher.h>

void* find_bl_verify_shsh(struct iboot_img* iboot_in) {
    int os_vers = get_os_version(iboot_in);
    
    /* Use the os-specific method for finding BL verify_shsh... */
    if(os_vers >= 5 && os_vers <= 7) {
        return find_bl_verify_shsh_5_6_7(iboot_in);
    }
    
    return find_bl_verify_shsh_generic(iboot_in);
}

void* find_ldr_ecid(struct iboot_img* iboot_in) {
    printf("%s: Entering...\n", __FUNCTION__);
    
    /* Find the LDR Rx, ='ECID' instruction... */
    void* ldr_insn = find_next_LDR_insn_with_value(iboot_in, 'ECID');
    if(!ldr_insn) {
        printf("%s: Unable to find LDR ECID!\n", __FUNCTION__);
        return 0;
    }
    
    printf("%s: Found LDR instruction at %p\n", __FUNCTION__, GET_IBOOT_FILE_OFFSET(iboot_in, ldr_insn));
    
    /* Resolve the BL verify_shsh routine from found instruction... */
    char *ldr_ecid = bl_search_down(ldr_insn,0x100);
    if(!ldr_ecid) {
        printf("%s: Unable to find a BL ECID! (Image may already be patched?)\n", __FUNCTION__);
        return 0;
    }
    
    printf("%s: Found BL ECID at %p\n", __FUNCTION__, GET_IBOOT_FILE_OFFSET(iboot_in, ldr_ecid));
    
    printf("%s: Leaving...\n", __FUNCTION__);
    
    return ldr_ecid;
}

void* find_ldr_bord(struct iboot_img* iboot_in) {
    printf("%s: Entering...\n", __FUNCTION__);
    
    /* Find the LDR Rx, ='BORD' instruction... */
    void* ldr_insn = find_next_LDR_insn_with_value(iboot_in, 'BORD');
    if(!ldr_insn) {
        printf("%s: Unable to find LDR insn!\n", __FUNCTION__);
        return 0;
    }
    
    printf("%s: Found LDR BORD instruction at %p\n", __FUNCTION__, GET_IBOOT_FILE_OFFSET(iboot_in, ldr_insn));
    
    /* Resolve the BL verify_shsh routine from found instruction... */
    char *ldr_bord = bl_search_down(ldr_insn,0x100);
    if(!ldr_bord) {
        printf("%s: Unable to find a BL BORD! (Image may already be patched?)\n", __FUNCTION__);
        return 0;
    }
    
    printf("%s: Found BL BORD at %p\n", __FUNCTION__, GET_IBOOT_FILE_OFFSET(iboot_in, ldr_bord));
    
    printf("%s: Leaving...\n", __FUNCTION__);
    
    return ldr_bord;
}

void* find_ldr_prod(struct iboot_img* iboot_in) {
    printf("%s: Entering...\n", __FUNCTION__);
    
    /* Find the LDR Rx, ='PROD' instruction... */
    void* ldr_insn = find_next_LDR_insn_with_value(iboot_in, 'PROD');
    if(!ldr_insn) {
        printf("%s: Unable to find LDR insn!\n", __FUNCTION__);
        return 0;
    }
    
    printf("%s: Found LDR PROD instruction at %p\n", __FUNCTION__, GET_IBOOT_FILE_OFFSET(iboot_in, ldr_insn));
    
    /* Resolve the BL verify_shsh routine from found instruction... */
    char *ldr_prod = bl_search_down(ldr_insn,0x100);
    if(!ldr_prod) {
        printf("%s: Unable to find a BL PROD! (Image may already be patched?)\n", __FUNCTION__);
        return 0;
    }
    
    printf("%s: Found BL PROD at %p\n", __FUNCTION__, GET_IBOOT_FILE_OFFSET(iboot_in, ldr_prod));
    
    printf("%s: Leaving...\n", __FUNCTION__);
    
    return ldr_prod;
}

void* find_ldr_sepo(struct iboot_img* iboot_in) {
    printf("%s: Entering...\n", __FUNCTION__);
    
    /* Find the LDR Rx, ='SEPO' instruction... */
    void* ldr_insn = find_next_LDR_insn_with_value(iboot_in, 'SEPO');
    if(!ldr_insn) {
        printf("%s: Unable to find LDR insn!\n", __FUNCTION__);
        return 0;
    }
    
    printf("%s: Found LDR SEPO instruction at %p\n", __FUNCTION__, GET_IBOOT_FILE_OFFSET(iboot_in, ldr_insn));
    
    /* Resolve the BL verify_shsh routine from found instruction... */
    char *ldr_sepo = bl_search_down(ldr_insn,0x100);
    if(!ldr_sepo) {
        printf("%s: Unable to find a BL SEPO! (Image may already be patched?)\n", __FUNCTION__);
        return 0;
    }
    
    printf("%s: Found BL SEPO at %p\n", __FUNCTION__, GET_IBOOT_FILE_OFFSET(iboot_in, ldr_sepo));
    
    printf("%s: Leaving...\n", __FUNCTION__);
    
    return ldr_sepo;
}

void* find_rsa_check_3_4(struct iboot_img* iboot_in) {
    printf("%s: Entering...\n", __FUNCTION__);

    /* Find Apple Secure Boot Certification Authority */
    void* rsa_cert_ldr = find_next_LDR_insn_with_str(iboot_in, RSA_STR);
    if(!rsa_cert_ldr) {
        printf("%s: Unable to find Certification LDR!\n", __FUNCTION__);
        return 0;
    }

    printf("%s: Found %s LDR at %p\n", __FUNCTION__, RSA_STR, GET_IBOOT_FILE_OFFSET(iboot_in, rsa_cert_ldr));

    /* Not sure how to do BL without using some offset (0x50) :/ */

    void* rsa_bl = bl_search_down(rsa_cert_ldr + 0x50, 0x100);
    if(!rsa_bl) {
        printf("%s: Could not find RSA BL!\n", __FUNCTION__);
        return 0;
    }

    printf("%s: Found RSA BL at %p\n", __FUNCTION__, GET_IBOOT_FILE_OFFSET(iboot_in, rsa_bl));

    void* rsa_bl_func = resolve_bl32(rsa_bl);
    if(!rsa_bl_func) {
        printf("%s: Failed to xref RSA BL!\n", __FUNCTION__);
        return 0;
    }

    printf("%s: RSA Function address: %p\n", __FUNCTION__, GET_IBOOT_FILE_OFFSET(iboot_in, rsa_bl_func));

    void* rsa_mov_neg1 = pattern_search(rsa_bl_func, 0x200, bswap32(MOVW_R0_NEG_1), bswap32(MOVW_R0_NEG_1), 1);
    if(!rsa_mov_neg1) {
        printf("%s: Failed to find MOV.W R0, #0xFFFFFFFF!\n", __FUNCTION__);

        void* rsa_movs_1 = pattern_search(rsa_bl_func + 0x150, 0x20, bswap32(MOV_NEGS_R0_1), bswap32(MOV_NEGS_R0_1), 1);
        if(!rsa_movs_1) {
            printf("%s: Failed to find MOVS R0, #1; NEGS R0, R0!\n", __FUNCTION__);
            return 0;
        }

        printf("%s: Found MOVS R0, #1; NEGS R0, R0 at %p\n", __FUNCTION__, GET_IBOOT_FILE_OFFSET(iboot_in, rsa_movs_1));
        rsa_mov_neg1 = rsa_movs_1;
    } else {
        printf("%s: Found MOV.W R0, #0xFFFFFFFF! at %p\n", __FUNCTION__, GET_IBOOT_FILE_OFFSET(iboot_in, rsa_mov_neg1));
    }

    printf("%s: Leaving...\n", __FUNCTION__);

    return rsa_mov_neg1;
}

void* find_bl_verify_shsh_5_6_7(struct iboot_img* iboot_in) {
    printf("%s: Entering...\n", __FUNCTION__);
    
    /* Find the MOVW Rx, #'RT' instruction... */
    void* movw = find_next_MOVW_insn_with_value(iboot_in->buf, iboot_in->len, 'RT');
    if(!movw) {
        printf("%s: Unable to find MOVW instruction!\n", __FUNCTION__);
        return 0;
    }
    
    printf("%s: Found MOVW instruction at %p\n", __FUNCTION__, GET_IBOOT_FILE_OFFSET(iboot_in, movw));
    
    /* Resolve the BL verify_shsh routine from found instruction... */
    void* bl_verify_shsh = find_bl_verify_shsh_insn(iboot_in, movw);
    if(!bl_verify_shsh) {
        printf("%s: Unable to find a BL verify_shsh! (Image may already be patched?)\n", __FUNCTION__);
        return 0;
    }
    
    void* bl_verify_shsh_next = find_bl_verify_shsh_insn_next(iboot_in, movw);
    if(!bl_verify_shsh_next) {
        printf("%s: Found BL verify_shsh at %p\n", __FUNCTION__, GET_IBOOT_FILE_OFFSET(iboot_in, bl_verify_shsh));
        
        printf("%s: Leaving...\n", __FUNCTION__);
        
        return bl_verify_shsh;
    }
    
    printf("%s: Found BL verify_shsh_next at %p\n", __FUNCTION__, GET_IBOOT_FILE_OFFSET(iboot_in, bl_verify_shsh_next));
    
    printf("%s: Leaving...\n", __FUNCTION__);
    
    return bl_verify_shsh_next;
}

void* find_bl_verify_shsh_generic(struct iboot_img* iboot_in) {
    printf("%s: Entering...\n", __FUNCTION__);
    
    /* Find the LDR Rx, ='CERT' instruction... */
    void* ldr_insn = find_next_LDR_insn_with_value(iboot_in, 'CERT');
    if(!ldr_insn) {
        printf("%s: Unable to find LDR insn!\n", __FUNCTION__);
        return 0;
    }
    
    printf("%s: Found LDR instruction at %p\n", __FUNCTION__, GET_IBOOT_FILE_OFFSET(iboot_in, ldr_insn));
    
    /* Resolve the BL verify_shsh routine from found instruction... */
    void* bl_verify_shsh = find_bl_verify_shsh_insn(iboot_in, ldr_insn);
    if(!bl_verify_shsh) {
        printf("%s: Unable to find a BL verify_shsh! (Image may already be patched?)\n", __FUNCTION__);
        return 0;
    }
    
    printf("%s: Found BL verify_shsh at %p\n", __FUNCTION__, GET_IBOOT_FILE_OFFSET(iboot_in, bl_verify_shsh));
    
    printf("%s: Leaving...\n", __FUNCTION__);
    
    return bl_verify_shsh;
}

void* find_bl_verify_shsh_insn(struct iboot_img* iboot_in, void* pc) {
    /* Find the top of the function... */
    void* function_top = find_verify_shsh_top(pc);
    if(!function_top) {
        printf("%s: Unable to find top of verify_shsh!\n", __FUNCTION__);
        return 0;
    }
    
    /* Find the BL insn resolving to this function... (BL verify_shsh seems to only happen once) */
    void* bl_verify_shsh = find_next_bl_insn_to(iboot_in, (uint32_t) ((uintptr_t)GET_IBOOT_FILE_OFFSET(iboot_in, function_top)));
    if(!bl_verify_shsh) {
        return 0;
    }
    
    return bl_verify_shsh;
}

void* find_bl_verify_shsh_insn_next(struct iboot_img* iboot_in, void* pc) {
    /* Find the top of the function... */
    void* function_top = find_verify_shsh_top(pc);
    if(!function_top) {
        printf("%s: Unable to find top of verify_shsh!\n", __FUNCTION__);
        return 0;
    }
    
    /* Find the BL insn resolving to this function... (BL verify_shsh seems to only happen once) */
    void* bl_verify_shsh = find_next_next_bl_insn_to(iboot_in, (uint32_t) ((uintptr_t)GET_IBOOT_FILE_OFFSET(iboot_in, function_top)));
    if(!bl_verify_shsh) {
        return 0;
    }
    
    return bl_verify_shsh;
}

void* find_dtre_get_value_bl_insn(struct iboot_img* iboot_in, const char* var) {
    printf("%s: Entering...\n", __FUNCTION__);
    
    /* Find the variable string... */
    void* var_str_loc = memstr(iboot_in->buf, iboot_in->len, var);
    if(!var_str_loc) {
        printf("%s: Unable to find %s string!\n", __FUNCTION__, var);
        return 0;
    }
    printf("%s: %s string is at %p\n", __FUNCTION__, var, (void*) GET_IBOOT_FILE_OFFSET(iboot_in, var_str_loc));
    
    /* Find the variable string xref... */
    void* var_xref = iboot_memmem(iboot_in, var_str_loc);
    if(!var_xref) {
        printf("%s: Unable to find %s string xref!\n", __FUNCTION__, var);
        return 0;
    }
    printf("%s: \"%s\" xref is at %p\n", __FUNCTION__, var, (void*) GET_IBOOT_FILE_OFFSET(iboot_in, var_xref));
    
    /* Locate corresponding LDR insn for xref... */
    void* var_ldr = ldr_to(var_xref);
    if(!var_ldr) {
        printf("%s: Unable to find %s string LDR from xref!\n", __FUNCTION__, var);
        return 0;
    }
    
    struct arm32_thumb_LDR* ldr_rd_debug_enabled = (struct arm32_thumb_LDR*) var_ldr;
    printf("%s: Found LDR R%d, =\"%s\" at %p\n", __FUNCTION__, ldr_rd_debug_enabled->rd, var, GET_IBOOT_FILE_OFFSET(iboot_in, var_ldr));
    
    /* Find the BL insn that follows the LDR insn... (Usually BL does_dtre_have_var) */
    void* is_in_dtre_bl = bl_search_down(var_ldr, 0x100);
    if(!is_in_dtre_bl) {
        printf("%s: Unable to find a BL following LDR insn.\n", __FUNCTION__);
        return 0;
    }
    is_in_dtre_bl++;
    
    /* Find the next BL insn after the previous BL insn... (Usually BL get_value_for_dtre_var) */
    void* get_value_for_dtre_bl = bl_search_down(is_in_dtre_bl, 0x100);
    if(!get_value_for_dtre_bl) {
        printf("%s: Unable to find a BL following the previous BL.\n", __FUNCTION__);
        return 0;
    }
    
    printf("%s: Found BL instruction at %p\n", __FUNCTION__, GET_IBOOT_FILE_OFFSET(iboot_in, get_value_for_dtre_bl));
    
    printf("%s: Leaving...\n", __FUNCTION__);
    
    return get_value_for_dtre_bl;
}

void* find_verify_shsh_top(void* ptr) {
    void* top = push_r4_r7_lr_search_up(ptr, 0x500);
    if(!top) {
        return 0;
    }
    top++; // Thumb
    return top;
}

uint32_t find_GETENV_Addr(struct iboot_img* iboot_in) {
    printf("%s: Finding network-type ldr\n", __FUNCTION__);
    void* network_type_ldr =  find_next_LDR_insn_with_str(iboot_in, "network-type");
    if(!network_type_ldr) {
        printf("%s: Failed to find network-type ldr\n", __FUNCTION__);
        return 0;
    }
    printf("%s: Found network-type ldr at %p\n", __FUNCTION__, GET_IBOOT_ADDR(iboot_in, network_type_ldr));
    printf("%s: Finding getenv bl\n", __FUNCTION__);
    void* network_type_bl = bl_search_down(network_type_ldr, 0x10);
    if(!network_type_bl) {
        printf("%s: Failed to find getenv bl\n", __FUNCTION__);
        return 0;
    }
    printf("%s: Found getenv bl at %p\n", __FUNCTION__, GET_IBOOT_ADDR(iboot_in, network_type_bl));
    printf("%s: Finding getenv address\n", __FUNCTION__);
    uint32_t GetENV_Addr = Resolve_BL_Long((uint32_t)GET_IBOOT_ADDR(iboot_in, network_type_bl), network_type_bl);
    printf("%s: Found getenv address at: 0x%x\n", __FUNCTION__, GetENV_Addr);
    return GetENV_Addr;
}

void* find_Boot_Args_String_Location(struct iboot_img* iboot_in) {
    printf("%s: Finding boot-args string location\n", __FUNCTION__);
    void* boot_args_str_loc = memstr(iboot_in->buf, iboot_in->len, "boot-args");
    if(!boot_args_str_loc) {
        printf("%s: Failed to find boot-args string location", __FUNCTION__);
        return 0;
    }
    return boot_args_str_loc;
}


void* find_Boot_Args_MOV(void* Search_Begin) {
    char* Potential_Mov = find_next_MOV_insn(Search_Begin, 0x10);
    if(!Potential_Mov) {
        printf("%s: Failed to find Last MOV\n", __FUNCTION__);
        return 0;
    }
    if(is_MOV_insn(Potential_Mov + 0x2)) {
        return (Potential_Mov + 0x2);
    }
    return Potential_Mov;
}
void* find_ldr_xref(struct iboot_img* iboot_in) {
    void* default_boot_args_str_loc = memstr(iboot_in->buf, iboot_in->len, DEFAULT_BOOTARGS_STR);
    if(!default_boot_args_str_loc) {
        printf("%s: Unable to find default boot-args string!\n", __FUNCTION__);
        return 0;
    }
    printf("%s: Default boot-args string is at %p\n", __FUNCTION__, (void*) GET_IBOOT_ADDR(iboot_in, default_boot_args_str_loc));
    
    void* default_boot_args_xref = iboot_memmem(iboot_in, default_boot_args_str_loc);
    if(!default_boot_args_xref) {
        printf("%s: Unable to find default boot-args string xref!\n", __FUNCTION__);
        return 0;
    }
    printf("%s: boot-args xref is at %p\n", __FUNCTION__, (void*) GET_IBOOT_ADDR(iboot_in, default_boot_args_xref));
    return default_boot_args_xref;
}
void* find_null_str(void* _mov_insn, int reg) {
    void* _Candidate = ldr_search_up(_mov_insn, 0x50);
    if(!_Candidate) {
        printf("%s: Failed to find ldr r%d, = null_str\n", __FUNCTION__, reg);
        return NULL;
    }
    struct arm32_thumb_LDR* Candidate = (struct arm32_thumb_LDR*) _Candidate;
    if(Candidate->rd == reg){
    return _Candidate;
    }
    else {
        printf("%s: Failed to find ldr r%d, = null_str\n", __FUNCTION__, reg);
        return NULL;
    }
}

void* find_boot_partition_ldr(struct iboot_img* iboot_in) {
    printf("%s: Entering...\n", __FUNCTION__);
    uint32_t boot_partition_loc = GET_IBOOT_ADDR(iboot_in, memmem(iboot_in -> buf, iboot_in -> len, "boot-partition", strlen("boot-partition")));
    if (!boot_partition_loc) {
        printf("%s: Failed to find boot-partition string\n", __FUNCTION__);
        return 0;
    }
    printf("%s: Found boot-partition string: %p\n", __FUNCTION__, boot_partition_loc);
    void * boot_partition_ldr = find_next_LDR_insn_with_value(iboot_in, boot_partition_loc);
    if (!boot_partition_ldr) {
        printf("%s: Failed to find boot-partition LDR\n", __FUNCTION__);
        return 0;
    }
    printf("%s: Found boot-partition LDR: %p\n", __FUNCTION__, GET_IBOOT_ADDR(iboot_in, boot_partition_ldr));
    return boot_partition_ldr;
}

void* find_boot_ramdisk_ldr(struct iboot_img* iboot_in) {
    printf("%s: Entering...\n", __FUNCTION__);
    uint32_t boot_ramdisk_loc = GET_IBOOT_ADDR(iboot_in, memmem(iboot_in -> buf, iboot_in -> len, "boot-ramdisk", strlen("boot-ramdisk")));
    if (!boot_ramdisk_loc) {
        printf("%s: Failed to find boot-ramdisk string\n", __FUNCTION__);
        return 0;
    }
    printf("%s: Found boot-ramdisk string: %p\n", __FUNCTION__, boot_ramdisk_loc);
    void * boot_ramdisk_ldr = find_next_LDR_insn_with_value(iboot_in, boot_ramdisk_loc);
    if (!boot_ramdisk_ldr) {
        printf("%s: Failed to find boot-ramdisk LDR\n", __FUNCTION__);
        return 0;
    }
    printf("%s: Found boot-ramdisk LDR: %p\n", __FUNCTION__, GET_IBOOT_ADDR(iboot_in, boot_ramdisk_ldr));
    return boot_ramdisk_ldr;
}

void* find_iloader_offsets(struct iboot_img* iboot_in) {
    uint32_t breakpoint1_addr = GET_IBOOT_FILE_OFFSET(iboot_in, memmem(iboot_in -> buf, iboot_in -> len, "\x2f\x28", strlen("\x2f\x28")));
    if (!breakpoint1_addr) {
        printf("%s: Failed to find cmp instruction\n", __FUNCTION__);
        return 0;
    }
    breakpoint1_addr += 0x44;
    printf("%s: Found breakpoint1_addr at %p\n", __FUNCTION__, breakpoint1_addr);
    
    /* fuck1-2-3_ADDR */
    void* fuck1_ADDR = memstr(iboot_in->buf, iboot_in->len, "\x48\x24\xb0\xfa");
    fuck1_ADDR += 0x14;
    if (!fuck1_ADDR) {
        printf("%s: Failed to find mov instruction\n", __FUNCTION__);
        return 0;
    }
    printf("%s: Found fuck1_ADDR at %p\n", __FUNCTION__, GET_IBOOT_FILE_OFFSET(iboot_in,fuck1_ADDR));
    fuck1_ADDR += 0x16;
    printf("%s: Found fuck2_ADDR at %p\n", __FUNCTION__, GET_IBOOT_FILE_OFFSET(iboot_in,fuck1_ADDR));
    uint32_t fuck3_ADDR_str = GET_IBOOT_ADDR(iboot_in, memmem(iboot_in -> buf, iboot_in -> len, "_memalign must be a power of two", strlen("_memalign must be a power of two")));
    if (!fuck3_ADDR_str) {
        printf("%s: Failed to find str\n", __FUNCTION__);
    }
    void* fuck3_ADDR = find_next_LDR_insn_with_value(iboot_in, fuck3_ADDR_str);
    if (!fuck3_ADDR) {
        printf("%s: Failed to find ldr instruction\n", __FUNCTION__);
    }
    fuck3_ADDR -= 0x22;
    printf("%s: Found fuck3_ADDR at %p\n", __FUNCTION__, GET_IBOOT_FILE_OFFSET(iboot_in,fuck3_ADDR));
    
    /* wait_for_event_ADDR */
    uint32_t wait_for_event_ADDR_str = GET_IBOOT_ADDR(iboot_in, memmem(iboot_in -> buf, iboot_in -> len, "0 < cp->c_resid", strlen("0 < cp->c_resid")));
    void* wait_for_event_ADDR = find_next_LDR_insn_with_value(iboot_in, wait_for_event_ADDR_str);
    void* bl1 = bl_search_down(wait_for_event_ADDR,0x100);
    uint32_t *dst1 = resolve_bl32(bl1);
    void* bl2 = bl_search_down(dst1,0x100);
    uint32_t *dst2 = resolve_bl32(bl2-0x4);
    printf("%s: Found wait_for_event_ADDR at %p\n", __FUNCTION__, GET_IBOOT_FILE_OFFSET(iboot_in, (void*)dst2));
    
    /* hugechunk_ADDR */
    void* hugechunk_ADDR = memstr(iboot_in->buf, iboot_in->len, "\x46\xf2\x6f\x70\xc6\xf6\x6f\x40");
    hugechunk_ADDR -= 0x58;
    printf("%s: Found hugechunk_ADDR at %p\n", __FUNCTION__,GET_IBOOT_FILE_OFFSET(iboot_in,hugechunk_ADDR));
    
    /* gpio_pin_state_ADDR */
    /*
     void* unknown_str = memstr(iboot_in->buf, iboot_in->len, "\x3a\x3a\x0a\x00");
     uint32_t* unknown_xref = iboot_memmem(iboot_in, unknown_str);
     void* unknown_ldr = ldr_to(unknown_xref);
     unknown_ldr -= 0x10;
     printf("%s: Found ldr at %p\n", __FUNCTION__,(void*) GET_IBOOT_FILE_OFFSET(iboot_in, unknown_ldr));
     void* bl_gpio = bl_search_up(unknown_ldr, 0x100);
     printf("%s: Found bl at %p\n", __FUNCTION__,(void*) GET_IBOOT_FILE_OFFSET(iboot_in, bl_gpio));
     uint32_t *dst = resolve_bl32(bl_gpio);
     printf("%s: Found gpio_pin_state_ADDR at %p\n", __FUNCTION__, (void*) GET_IBOOT_FILE_OFFSET(iboot_in, (void*)dst-1));
     */ // this offset changes on some devices, it can't be universally found
    
    /* readp_ADDR */
    
    void* readp_ADDR = memstr(iboot_in->buf, iboot_in->len, "\xD0\xF8\x24\x90");
    readp_ADDR -= 0xC;
    printf("%s: Found readp_ADDR at %p\n", __FUNCTION__,GET_IBOOT_FILE_OFFSET(iboot_in,readp_ADDR));
    
    /* get_mem_size_ADDR */
    /*
    void* get_mem_size_ADDR = memstr(iboot_in->buf, iboot_in->len, "\xA5\xFB\x01\x02");
    get_mem_size_ADDR -= 0x18;
    printf("%s: Found get_mem_size_ADDR at %p\n", __FUNCTION__,GET_IBOOT_FILE_OFFSET(iboot_in,get_mem_size_ADDR));
     */ // this offset changes on some devices, it can't be universally found
    
    /* putchar_ADDR */
    
    void* putchar_ADDR = memstr(iboot_in->buf, iboot_in->len, "\x01\xAF\x04\xbf");
    putchar_ADDR -= 0x6;
    printf("%s: Found putchar_ADDR at %p\n", __FUNCTION__,GET_IBOOT_FILE_OFFSET(iboot_in,putchar_ADDR));
    
    /* adjust_stack_ADDR */
    
    void* main_str = memstr(iboot_in->buf, iboot_in->len, "\x6d\x61\x69\x6e\x00");
    uint32_t* main_xref = iboot_memmem(iboot_in, main_str);
    void* main_ldr = ldr_to(main_xref);
    main_ldr -= 0x8;
    uint32_t *dst = resolve_bl32(main_ldr);
    printf("%s: Found adjust_stack_ADDR at %p\n", __FUNCTION__, (void*) GET_IBOOT_FILE_OFFSET(iboot_in, (void*)dst-1));
    
    /* adjust_environ_ADDR */
    
    void* false_resume_str = memstr(iboot_in->buf, iboot_in->len, "false == resume");
    uint32_t* false_resume_xref = iboot_memmem(iboot_in, false_resume_str);
    void* adjust_environ_ADDR = false_resume_xref;
    printf("%s: Found adjust_environ_ADDR at %p\n", __FUNCTION__, GET_IBOOT_FILE_OFFSET(iboot_in,adjust_environ_ADDR + 4));
    
    /* disable_interrupts_ADDR */
    
    void* disable_interrupts_ADDR = memstr(iboot_in->buf, iboot_in->len, "\xb2\xf5\x7a\x7f");
    disable_interrupts_ADDR += 0x1c;
    uint32_t *dst3 = resolve_bl32(disable_interrupts_ADDR);
    printf("%s: Found disable_interrupts_ADDR at %p\n", __FUNCTION__, GET_IBOOT_FILE_OFFSET(iboot_in, (void*)dst3-1));
    
    /* cache_stuff_ADDR */
    
    void* mov_instr = memstr(iboot_in->buf, iboot_in->len, "\x4e\xf2\xf8\x71\xcf\xf6\xbf\x71");
    void* cache_stuff_ADDR = push_r7_lr_search_up(mov_instr, 0x500);
    printf("%s: Found cache_stuff_ADDR at %p\n", __FUNCTION__, GET_IBOOT_FILE_OFFSET(iboot_in,cache_stuff_ADDR));
    
    /* wtf_ADDR */
    
    uint32_t wtf_ADDR = GET_IBOOT_ADDR(iboot_in, memmem(iboot_in -> buf, iboot_in -> len, "\x50\xE8\x00\x1F\x21\xF0\x01\x01\x01\x60\x70\x47", strlen("\x50\xE8\x00\x1F\x21\xF0\x01\x01\x01\x60\x70\x47")));
    if (!wtf_ADDR) {
        printf("%s: Failed to find wtf_ADDR\n", __FUNCTION__);
        printf("%s: You have to find it\n", __FUNCTION__);
    }
    printf("%s: Found wtf_ADDR at %p\n", __FUNCTION__,wtf_ADDR);
    
    /* iboot_warmup_ADDR */
    
    void* iboot_warmup_ADDR = memstr(iboot_in->buf, iboot_in->len, "\x1f\x00\xc0\xe3");
    if (!iboot_warmup_ADDR) {
        printf("%s: Failed to find wtf_ADDR\n", __FUNCTION__);
        printf("%s: You have to find it\n", __FUNCTION__);
    }
    iboot_warmup_ADDR += 0x5c;
    printf("%s: Found iboot_warmup_ADDR at %p\n", __FUNCTION__, GET_IBOOT_FILE_OFFSET(iboot_in,iboot_warmup_ADDR));
    
    /* iboot_start_ADDR */
    
    uint32_t root_str = GET_IBOOT_ADDR(iboot_in, memmem(iboot_in -> buf, iboot_in -> len, "root filesystem mount failed", strlen("root filesystem mount failed")));
    void* root_ldr = find_next_LDR_insn_with_value(iboot_in, root_str);
    void* iboot_start_ADDR = push_r7_lr_search_down(root_ldr, 0x500);
    printf("%s: Found iboot_start_ADDR at %p\n", __FUNCTION__, GET_IBOOT_FILE_OFFSET(iboot_in,iboot_start_ADDR));
    
    /* main_task_ADDR */
    
    void* main_task_ADDR = push_r4_r7_lr_search_up(hugechunk_ADDR, 0x500);
    printf("%s: Found main_task_ADDR at %p\n", __FUNCTION__, GET_IBOOT_FILE_OFFSET(iboot_in,main_task_ADDR));
    
    /* panic_ADDR */
    
    uint32_t stack_str = GET_IBOOT_ADDR(iboot_in, memmem(iboot_in -> buf, iboot_in -> len, "stack corrupted", strlen("stack corrupted")));
    void* stack_ldr = find_next_LDR_insn_with_value(iboot_in, stack_str);
    void* panic_ADDR = push_r4_r7_lr_search_up(stack_ldr, 0x500);
    printf("%s: Found panic_ADDR at %p\n", __FUNCTION__,GET_IBOOT_FILE_OFFSET(iboot_in,panic_ADDR-2));
    
    /* system_init_ADDR */
    
    void* system_init_ADDR = bl_search_down(iboot_start_ADDR, 0x100);
    system_init_ADDR += 4;
    uint32_t *dst4 = resolve_bl32(system_init_ADDR);
    printf("%s: Found system_init_ADDR at %p\n", __FUNCTION__, (void*) GET_IBOOT_FILE_OFFSET(iboot_in, (void*)dst4-1));

    /* task_create_ADDR */
    
    system_init_ADDR += 10;
    void* task_create_ADDR = bl_search_down(system_init_ADDR, 0x20);
    uint32_t *dst5 = resolve_bl32(task_create_ADDR);
    printf("%s: Found task_create_ADDR at %p\n", __FUNCTION__, (void*) GET_IBOOT_FILE_OFFSET(iboot_in, (void*)dst5-1));
    
    /* task_start_ADDR */
    
    task_create_ADDR += 4;
    uint32_t *dst6 = resolve_bl32(task_create_ADDR);
    printf("%s: Found task_start_ADDR at %p\n", __FUNCTION__, (void*) GET_IBOOT_FILE_OFFSET(iboot_in, (void*)dst6-1));
    
    /* task_exit_ADDR */
    
    char *next_bl = bl_search_down(dst6,0x100);
    void* task_exit_ADDR = push_r7_lr_search_down(next_bl, 0x500);
    printf("%s: Found task_exit_ADDR at %p\n", __FUNCTION__,GET_IBOOT_FILE_OFFSET(iboot_in, task_exit_ADDR));
    
    /* printf_ADDR */
    
    uint32_t panic_str = GET_IBOOT_ADDR(iboot_in, memmem(iboot_in -> buf, iboot_in -> len, "Panic saved, full reset.", strlen("Panic saved, full reset.")));
    void* panic_ldr = find_next_LDR_insn_with_value(iboot_in, panic_str);
    void* printf_ADDR = bl_search_down(panic_ldr, 0x100);
    uint32_t *dst7 = resolve_bl32(printf_ADDR);
    printf("%s: Found printf_ADDR at %p\n", __FUNCTION__, (void*) GET_IBOOT_FILE_OFFSET(iboot_in, (void*)dst7-1));
    
    /* malloc_ADDR */
    
    uint32_t boot_ramdisk_str = GET_IBOOT_ADDR(iboot_in, memmem(iboot_in -> buf, iboot_in -> len, "boot-ramdisk", strlen("boot-ramdisk")));
    void* boot_ramdisk_ldr = find_next_LDR_insn_with_value(iboot_in, boot_ramdisk_str);
    void* push_instr = push_r4_r7_lr_search_up(boot_ramdisk_ldr, 0x500);
    void* malloc_ADDR = bl_search_down(push_instr, 0x100);
    uint32_t *dst8 = resolve_bl32(malloc_ADDR);
    printf("%s: Found malloc_ADDR at %p\n", __FUNCTION__, (void*) GET_IBOOT_FILE_OFFSET(iboot_in, (void*)dst8-1));
    
    
    /* free_ADDR */
    
    uint32_t ramdisk_file_str = GET_IBOOT_ADDR(iboot_in, memmem(iboot_in -> buf, iboot_in -> len, "ramdisk file invalid", strlen("ramdisk file invalid")));
    void* ramdisk_file_ldr = find_next_LDR_insn_with_value(iboot_in,ramdisk_file_str);
    void* push_instr2 = find_next_CMP_insn_with_value(ramdisk_file_ldr, 0x100, 0);
    void* free_ADDR = bl_search_down(push_instr2, 0x100);
    uint32_t *dst9 = resolve_bl32(free_ADDR);
    printf("%s: Found free_ADDR at %p\n", __FUNCTION__, (void*) GET_IBOOT_FILE_OFFSET(iboot_in, (void*)dst9-1));
    
    /* create_envvar_ADDR */
    
    uint32_t build_style_str = GET_IBOOT_ADDR(iboot_in, memmem(iboot_in -> buf, iboot_in -> len, "build-style", strlen("build-style")));
    void* build_style_ldr = find_next_LDR_insn_with_value(iboot_in,build_style_str);
    void* create_envvar_ADDR = bl_search_down(build_style_ldr, 0x100);
    uint32_t *dst10 = resolve_bl32(create_envvar_ADDR);
    printf("%s: Found create_envvar_ADDR at %p\n", __FUNCTION__, (void*) GET_IBOOT_FILE_OFFSET(iboot_in, (void*)dst10-1));
    
    /* bcopy_ADDR */
    
    uint32_t hfs_str = GET_IBOOT_ADDR(iboot_in, memmem(iboot_in -> buf, iboot_in -> len, "HFSInitPartition: %p", strlen("HFSInitPartition: %p")));
    void* hfs_ldr = find_next_LDR_insn_with_value(iboot_in,hfs_str);
    void* bcopy_ADDR = blx_search_up(hfs_ldr, 0x500);
    uint32_t *dst11 = resolve_bl32(bcopy_ADDR);
    printf("%s: Found bcopy_ADDR at %p\n", __FUNCTION__, (void*) GET_IBOOT_FILE_OFFSET(iboot_in, (void*)dst11));
    
    /* decompress_lzss_ADDR */
    
    void* mov_instr1 = memstr(iboot_in->buf, iboot_in->len, "\x46\xf2\x62\x72");
    void* decompress_lzss_ADDR = bl_search_up(mov_instr1, 0x500);
    uint32_t *dst12 = resolve_bl32(decompress_lzss_ADDR);
    printf("%s: Found decompress_lzss_ADDR at %p\n", __FUNCTION__, (void*) GET_IBOOT_FILE_OFFSET(iboot_in, (void*)dst12-1));
    return 0;
}

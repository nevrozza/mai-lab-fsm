//
// Created by nevrozq on 05.01.2026.
//

#include "fsm.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct FSM {
    FSMState current_state;
    uint64_t bcd_count;

    uint32_t digit_count; // Если кратно 4 -> полнотелое!!
};

FSM *fsm_create() {
    FSM *fsm = malloc(sizeof(FSM));
    if (fsm == NULL) {
        perror("MemoryError");
        return NULL; // stfu IDE
    }
    fsm->current_state = AT_START;
    fsm->bcd_count = 0;
    return fsm;
}

bool is_separator(const uint32_t c) {
    return c == ' ' || c == '\n' || c == '\t' ||
           c == ',' || c == '.' ||
           c == '\r' || c == 0;
}

bool is_digit(const uint32_t c) {
    return c >= '0' && c <= '9';
}

void start_case(FSM *fsm, const uint32_t c) {
    if (is_separator(c)) {
        // skip
    } else if (c == '+' || c == '-') {
        fsm->digit_count = 0;
        fsm->current_state = IN_BCD;
    } else if (is_digit(c)) {
        fsm->digit_count = 1;
        fsm->current_state = IN_BCD;
    } else {
        fsm->current_state = IN_WORD;
    }
}

void bcd_case(FSM *fsm, const uint32_t c) {
    if (is_separator(c)) {
        // Число закончилось
        if (fsm->digit_count % 4 == 0) {
            fsm->bcd_count++;
        }
        fsm->current_state = AT_START;
    } else if (!is_digit(c)) {
        // Это оказалось не число =(
        fsm->current_state = IN_WORD;
    } else {
        fsm->digit_count++;
    }
}

void word_case(FSM *fsm, const uint32_t c) {
    if (is_separator(c)) {
        fsm->current_state = AT_START;
    }
}


void fsm_step(FSM *fsm, const uint32_t c) {
    switch (fsm->current_state) {
        case AT_START:
            start_case(fsm, c);
            break;
        case IN_BCD:
            bcd_case(fsm, c);
            break;
        case IN_WORD:
            word_case(fsm, c);
            break;
    }
}

// corner case
void fsm_finish(FSM *fsm) {
    if (fsm->current_state == IN_BCD && fsm->digit_count%4 == 0) {
        fsm->bcd_count++;
    }
}

uint64_t fsm_get_bcd_count(const FSM *fsm) {
    return fsm->bcd_count;
}
#pragma once

#include "subghz_protocol_common.h"

typedef struct SubGhzProtocolCameAtomo SubGhzProtocolCameAtomo;

/** Allocate SubGhzProtocolCameAtomo
 * 
 * @return SubGhzProtocolCameAtomo* 
 */
SubGhzProtocolCameAtomo* subghz_protocol_came_atomo_alloc();

/** Free SubGhzProtocolCameAtomo
 * 
 * @param instance 
 */
void subghz_protocol_came_atomo_free(SubGhzProtocolCameAtomo* instance);

/** File name rainbow table CAME Atomo
 * 
 * @param instance - SubGhzProtocolCameAtomo instance
 * @param file_name - "path/file_name"
 */
void subghz_protocol_came_atomo_name_file(SubGhzProtocolCameAtomo* instance, const char* name);

// /** Get upload protocol
//  *
//  * @param instance - SubGhzProtocolCameAtomo instance
//  * @param encoder - SubGhzProtocolCommonEncoder encoder
//  * @return bool
//  */
// bool subghz_protocol_came_atomo_send_key(
//     SubGhzProtocolCameAtomo* instance,
//     SubGhzProtocolCommonEncoder* encoder);

/** Reset internal state
 * @param instance - SubGhzProtocolCameAtomo instance
 */
void subghz_protocol_came_atomo_reset(SubGhzProtocolCameAtomo* instance);

/** Parse accepted duration
 * 
 * @param instance - SubGhzProtocolCameAtomo instance
 * @param data - LevelDuration level_duration
 */
void subghz_protocol_came_atomo_parse(
    SubGhzProtocolCameAtomo* instance,
    bool level,
    uint32_t duration);

/** Outputting information from the parser
 * 
 * @param instance - SubGhzProtocolCameAtomo* instance
 * @param output   - output string
 */
void subghz_protocol_came_atomo_to_str(SubGhzProtocolCameAtomo* instance, string_t output);

// /** Get a string to save the protocol
//  *
//  * @param instance  - SubGhzProtocolCameAtomo instance
//  * @param output    - the resulting string
//  */
// void subghz_protocol_came_atomo_to_save_str(SubGhzProtocolCameAtomo* instance, string_t output);

// /** Loading protocol from file
//  *
//  * @param file_worker - FileWorker file_worker
//  * @param instance - SubGhzProtocolCameAtomo instance
//  * @param file_path - file path
//  * @return bool
//  */
// bool subghz_protocol_came_atomo_to_load_protocol_from_file(
//     FileWorker* file_worker,
//     SubGhzProtocolCameAtomo* instance,
//     const char* file_path);

/** Loading protocol from bin data
 * 
 * @param instance - SubGhzProtocolCameAtomo instance
 * @param context - SubGhzProtocolCommonLoad context
 */
void subghz_decoder_came_atomo_to_load_protocol(SubGhzProtocolCameAtomo* instance, void* context);
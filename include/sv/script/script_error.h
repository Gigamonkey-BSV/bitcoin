// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2016 The Bitcoin Core developers
// Copyright (c) 2019 Bitcoin Association
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef BSV_SCRIPT_SCRIPT_ERROR_H
#define BSV_SCRIPT_SCRIPT_ERROR_H

#include <iosfwd>

namespace bsv {

typedef enum ScriptError_t
{
    SCRIPT_ERR_OK = 0,
    SCRIPT_ERR_UNKNOWN_ERROR,
    SCRIPT_ERR_EVAL_FALSE,
    SCRIPT_ERR_OP_RETURN,

    /* Max sizes */
    SCRIPT_ERR_SCRIPT_SIZE,
    SCRIPT_ERR_PUSH_SIZE,
    SCRIPT_ERR_OP_COUNT,
    SCRIPT_ERR_STACK_SIZE,
    SCRIPT_ERR_SIG_COUNT,
    SCRIPT_ERR_PUBKEY_COUNT,

    /* Operands checks */
    SCRIPT_ERR_INVALID_OPERAND_SIZE,
    SCRIPT_ERR_INVALID_NUMBER_RANGE,
    SCRIPT_ERR_IMPOSSIBLE_ENCODING,
    SCRIPT_ERR_INVALID_SPLIT_RANGE,
    SCRIPT_ERR_SCRIPTNUM_OVERFLOW,
    SCRIPT_ERR_SCRIPTNUM_MINENCODE,

    /* Failed verify operations */
    SCRIPT_ERR_VERIFY,
    SCRIPT_ERR_EQUALVERIFY,
    SCRIPT_ERR_CHECKMULTISIGVERIFY,
    SCRIPT_ERR_CHECKSIGVERIFY,
    SCRIPT_ERR_NUMEQUALVERIFY,

    /* Logical/Format/Canonical errors */
    SCRIPT_ERR_BAD_OPCODE,
    SCRIPT_ERR_DISABLED_OPCODE,
    SCRIPT_ERR_INVALID_STACK_OPERATION,
    SCRIPT_ERR_INVALID_ALTSTACK_OPERATION,
    SCRIPT_ERR_UNBALANCED_CONDITIONAL,

    /* Divisor errors */
    SCRIPT_ERR_DIV_BY_ZERO,
    SCRIPT_ERR_MOD_BY_ZERO,

    /* CHECKLOCKTIMEVERIFY and CHECKSEQUENCEVERIFY */
    SCRIPT_ERR_NEGATIVE_LOCKTIME,
    SCRIPT_ERR_UNSATISFIED_LOCKTIME,

    /* Malleability */
    SCRIPT_ERR_SIG_HASHTYPE,
    SCRIPT_ERR_SIG_DER,
    SCRIPT_ERR_MINIMALDATA,
    SCRIPT_ERR_SIG_PUSHONLY,
    SCRIPT_ERR_SIG_HIGH_S,
    SCRIPT_ERR_SIG_NULLDUMMY,
    SCRIPT_ERR_PUBKEYTYPE,
    SCRIPT_ERR_CLEANSTACK,
    SCRIPT_ERR_MINIMALIF,
    SCRIPT_ERR_SIG_NULLFAIL,

    /* softfork safeness */
    SCRIPT_ERR_DISCOURAGE_UPGRADABLE_NOPS,

    /* misc */
    SCRIPT_ERR_NONCOMPRESSED_PUBKEY,

    /* anti replay */
    SCRIPT_ERR_ILLEGAL_FORKID,
    SCRIPT_ERR_MUST_USE_FORKID,

    SCRIPT_ERR_BIG_INT,

    SCRIPT_ERR_ERROR_COUNT
} ScriptError;

#define SCRIPT_ERR_LAST SCRIPT_ERR_ERROR_COUNT

const char *ScriptErrorString(const ScriptError error);

std::ostream& operator<<(std::ostream&, const ScriptError);

}

#endif // BSV_SCRIPT_SCRIPT_ERROR_H

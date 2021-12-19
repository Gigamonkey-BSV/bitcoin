// Copyright (c) 2021 Katrina Knight
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef GIGAMONKEY_CONSTANTS_HPP
#define GIGAMONKEY_CONSTANTS_HPP

#define GIGAMONKEY_P2P_VERSION 70015
#define GIGAMONKEY_P2P_USER_AGENT "/Gigamonkey/"

#define GIGAMONKEY_P2P_VERSION_MINIMUM 106
#define GIGAMONKEY_P2P_VERSION_HEIGHT 209
#define GIGAMONKEY_P2P_VERSION_RELAY 70001

enum class RejectCodes {
  REJECT_MALFORMED = 0x01,
  REJECT_INVALID = 0x10,
  REJECT_OBSOLETE = 0x11,
  REJECT_DUPLICATE = 0x12,
  REJECT_NONSTANDARD = 0x40,
  REJECT_DUST = 0x41,
  REJECT_INSUFFICIENTFEE = 0x42,
  REJECT_CHECKPOINT = 0x43
};
#endif //GIGAMONKEY_CONSTANTS_HPP
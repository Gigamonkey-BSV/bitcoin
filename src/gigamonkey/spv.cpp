// Copyright (c) 2019 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#include <gigamonkey/spv.hpp>

namespace Gigamonkey::Bitcoin {
    
    block genesis() {
        static block Genesis = block{bytes(encoding::hex::string{std::string{} + 
            "0100000000000000000000000000000000000000000000000000000000000000" +
            "000000003BA3EDFD7A7B12B27AC72C3E67768F617FC81BC3888A51323A9FB8AA" +
            "4B1E5E4A29AB5F49FFFF001D1DAC2B7C01010000000100000000000000000000" +
            "00000000000000000000000000000000000000000000FFFFFFFF4D04FFFF001D" +
            "0104455468652054696D65732030332F4A616E2F32303039204368616E63656C" +
            "6C6F72206F6E206272696E6B206F66207365636F6E64206261696C6F75742066" +
            "6F722062616E6B73FFFFFFFF0100F2052A01000000434104678AFDB0FE554827" +
            "1967F1A67130B7105CD6A828E03909A67962E0EA1F61DEB649F6BC3F4CEF38C4" +
            "F35504E51EC112DE5C384DF7BA0B8D578A4C702B6BF11D5FAC00000000"})};
        return Genesis;
    }
    
}

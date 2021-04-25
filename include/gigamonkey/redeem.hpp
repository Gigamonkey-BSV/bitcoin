// Copyright (c) 2019-2021 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef GIGAMONKEY_REDEEM
#define GIGAMONKEY_REDEEM

#include <gigamonkey/ledger.hpp>
#include <gigamonkey/script/pattern.hpp>
#include <gigamonkey/wif.hpp>

namespace Gigamonkey::Bitcoin {
    
    struct redeemer {
        // This information must be provided in the event that a signature is required. 
        // However, not all input scripts have signatures. Therefore, we can't assume that
        // a key is here either or that any signature is created. 
        virtual bytes redeem(const signature::document& document, sighash::directive d) const = 0;
        virtual uint32 expected_size() const = 0;
        virtual uint32 sigops() const = 0;
    };
    
    struct spendable : ledger::prevout {
        ptr<redeemer> Redeemer;
        
        spendable(const ledger::prevout& p, ptr<redeemer> r) : ledger::prevout{p}, Redeemer{r} {}
        
        input operator()(const incomplete::transaction tx, index i, sighash::directive d) {
            if (Redeemer == nullptr) return {};
            incomplete::input in = tx.Inputs[i];
            if (ledger::prevout::Key != in.Reference) return {};
            return in.complete(Redeemer->redeem(signature::document{ledger::prevout::Value, tx, i}, d));
        }
        
        satoshi value() const {
            return ledger::prevout::Value.Value;
        }
        
        outpoint reference() const {
            return ledger::prevout::Key;
        }
        
    };
    
    ledger::vertex redeem(list<spendable> prev, list<output> out, uint32_little locktime = 0);
    
    struct spend_input {
        uint32_little Sequence;
        sighash::directive Directive;
        
        spend_input() : Sequence{input::Finalized}, Directive{sighash::all} {}
        spend_input(uint32_little x, sighash::directive d) : Sequence{x}, Directive{d} {}
    };
    
    ledger::vertex redeem(list<std::pair<spendable, spend_input>> prev, list<output> out, uint32_little locktime = 0);

    ledger::vertex inline redeem(list<spendable> prev, list<output> out, uint32_little locktime) {
        return redeem(data::for_each([](spendable p) -> std::pair<spendable, spend_input> {
            return {p, spend_input{}};
        }, prev), out, locktime);
    }
    
    struct redeem_pay_to_pubkey final : redeemer {
        secret Secret;
        
        redeem_pay_to_pubkey(const secret& s) : Secret{s} {}
        
        bytes redeem(const signature::document& document, sighash::directive d) const override {
            return pay_to_pubkey::redeem(Secret.sign(document, d));
        }
        
        uint32 expected_size() const override {
            return signature::MaxSignatureSize + 1;
        };
        
        uint32 sigops() const override {
            return 1;
        }
    };
    
    struct redeem_pay_to_address final : redeemer {
        secret Secret;
        pubkey Pubkey;
        
        redeem_pay_to_address(const secret& s, const pubkey& p) : Secret{s}, Pubkey{p} {}
        
        bytes redeem(const signature::document& document, sighash::directive d) const override {
            return pay_to_address::redeem(Secret.sign(document, d), Pubkey);
        }
        
        uint32 expected_size() const override {
            return signature::MaxSignatureSize + Pubkey.size() + 2;
        };
        
        uint32 sigops() const override {
            return 1;
        }

    };
    
    std::ostream inline &operator<<(std::ostream &o, const spendable& x) {
        return o << "{" << static_cast<ledger::prevout>(x) << "}";
    };
    
}

#include <gigamonkey/schema/keysource.hpp>
#include <gigamonkey/script/pattern.hpp>

namespace Gigamonkey::Bitcoin {
    
    struct change {
        bytes OutputScript;
        ptr<redeemer> Redeemer;
    };
    
    struct output_pattern {
        virtual change create_redeemable(ptr<keysource>&) const = 0;
    };
    
    struct pay_to_pubkey_pattern : output_pattern {
        pay_to_pubkey_pattern() : output_pattern{} {}
        change create_redeemable(ptr<keysource>& k) const override {
            secret s = k->first();
            k = k->rest();
            return change{pay_to_pubkey::script(s.to_public()),
                std::make_shared<redeem_pay_to_pubkey>(s)};
        };
    };
    
    struct pay_to_address_pattern : output_pattern {
        pay_to_address_pattern() : output_pattern{} {}
        change create_redeemable(ptr<keysource>& k) const override {
            secret s = k->first();
            k = k->rest();
            return change{pay_to_address::script(s.address().Digest), 
                std::make_shared<redeem_pay_to_address>(s, s.to_public())};
        };
    };
    
}

#endif

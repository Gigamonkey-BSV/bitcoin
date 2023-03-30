// Copyright (c) 2020-2021 Daniel Krawisz
// Distributed under the Open BSV software license, see the accompanying file LICENSE.

#ifndef GIGAMONKEY_STRATUM_STRATUM
#define GIGAMONKEY_STRATUM_STRATUM

#include <gigamonkey/stratum/error.hpp>
#include <gigamonkey/stratum/method.hpp>
#include <gigamonkey/stratum/message_id.hpp>

// Description of Stratum: 
// https://docs.google.com/document/d/1ocEC8OdFYrvglyXbag1yi8WoskaZoYuR5HGhwf0hWAY

namespace Gigamonkey::Stratum {
    
    using parameters = JSON::array_t;
    
    template <typename X> using optional = maybe<X>;
    
    struct notification : JSON {
        
        static bool valid (const JSON &);
        
        static Stratum::method method (const JSON &);
        static parameters params (const JSON &);
        
        bool valid () const;
        
        Stratum::method method () const;
        parameters params () const;
        
        notification ();
        notification (Stratum::method m, const parameters &p);
        explicit notification (const JSON &j) : JSON (j) {}
    };
    
    struct request : JSON {
        
        static bool valid (const JSON &);
        
        static message_id id (const JSON &);
        static Stratum::method method (const JSON &);
        static parameters params (const JSON &);
        
        bool valid () const;
        
        message_id id () const;
        Stratum::method method () const;
        parameters params () const;
        
        request ();
        request (message_id id, Stratum::method m, const parameters &p);
        explicit request (const JSON &j) : JSON (j) {}
    };
    
    struct response : JSON {
        
        static bool valid(const JSON &);
        
        static message_id id (const JSON &);
        static JSON result (const JSON &);
        static optional<Stratum::error> error (const JSON &);
        
        bool valid () const {
            return valid (*this);
        }
        
        message_id id () const;
        JSON result () const;
        optional<Stratum::error> error () const;
        
        response ();
        response (message_id id, const JSON &p);
        response (message_id id, const JSON &p, const Stratum::error &e);
        explicit response (const JSON &j) : JSON (j) {}
        
        bool is_error () const {
            return bool (error ());
        }
        
    };
    
    inline request::request () : JSON {} {}
    
    inline request::request (message_id id, Stratum::method m, const parameters &p) :
        JSON {{"id", id}, {"method", method_to_string (m)}, {"params", p}} {}
    
    bool inline request::valid (const JSON &j) {
        return request::method (j) != unset && j.contains ("params") &&
            j["params"].is_array () && j.contains ("id") && message_id::valid (j["id"]);
    }
    
    bool inline request::valid () const {
        return valid (*this);
    }
        
    message_id inline request::id () const {
        return id (*this);
    }
    
    Stratum::method inline request::method () const {
        return method (*this);
    }
    
    parameters inline request::params () const {
        return params (*this);
    }
    
    inline notification::notification () : JSON{} {}
    
    inline notification::notification (Stratum::method m, const parameters& p) :
        JSON{{"id", nullptr}, {"method"}, {"params", p}} {}
    
    bool inline notification::valid (const JSON &j) {
        return notification::method (j) != unset && j.contains ("params") &&
            j["params"].is_array () && j.contains ("id") && j["id"].is_null ();
    }
    
    bool inline notification::valid () const {
        return valid (*this);
    }
    
    Stratum::method inline notification::method () const {
        return method (*this);
    }
    
    parameters inline notification::params () const {
        return params (*this);
    }
    
    inline response::response () : JSON {} {}
    
    inline response::response (message_id id, const JSON &p) :
        JSON {{"id", id}, {"result", p}, {"error", nullptr}} {}
    
    inline response::response (message_id id, const JSON &p, const Stratum::error &e) :
        JSON {{"id", id}, {"result", p}, {"error", JSON (e)}} {}
    
    message_id inline response::id () const {
        return id (*this);
    }
    
    JSON inline response::result () const {
        return result (*this);
    }
    
    optional<Stratum::error> inline response::error () const {
        return error (*this);
    }
    
}

#endif 


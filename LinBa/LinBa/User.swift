//
//  User.swift
//  LinBa
//
//  Created by Kirill Baranov on 02.03.17.
//  Copyright © 2017 Kirill Baranov. All rights reserved.
//

import UIKit
import ObjectMapper

class User: NSObject {
    
    var name: String?
    var token: String?
    
    init(name: String?, token: String?) {
        self.name = name
        self.token = token
    }
    

}

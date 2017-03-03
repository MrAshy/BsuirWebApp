//
//  Error.swift
//  LinBa
//
//  Created by Kirill Baranov on 01.03.17.
//  Copyright © 2017 Kirill Baranov. All rights reserved.
//

import UIKit

class APIError: Error {
    
    var desc: String
    
    init(desc: String) {
        self.desc = desc
    }
}

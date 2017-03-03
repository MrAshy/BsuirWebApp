//
//  Producer.swift
//  LinBa
//
//  Created by Kirill Baranov on 01.03.17.
//  Copyright © 2017 Kirill Baranov. All rights reserved.
//

import UIKit
import ObjectMapper

class Producer: Mappable {
    
    var id: Int?
    var name: String?
    var lastName: String?
    var year: Int?
    var country: String?
    var imageLink: String?
    
    required init?(map: Map) {
        
    }
    
    func mapping(map: Map) {
        id <- map["id"]
        name <- map["name"]
        lastName <- map["sname"]
        year <- map["year"]
        country <- map["country"]
        imageLink <- map["imageLink"]
    }

}

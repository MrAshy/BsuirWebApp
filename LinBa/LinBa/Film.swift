//
//  Film.swift
//  LinBa
//
//  Created by Kirill Baranov on 01.03.17.
//  Copyright © 2017 Kirill Baranov. All rights reserved.
//

/*
 <obj: Film>
	{
 "id" : <int>,
 "name" : <string>,
 "year" : <int>,
 "rate" : <double>,
 "trailerLink" : <string>,
 "imageLink" : <string>,
 "producerId" : <int>,
 "country" : [ <string> ]
	}
 //-----------*/

import UIKit
import ObjectMapper

class Film: Mappable {
    
    var id: Int?
    var name: String?
    var year: Int?
    var rate: Double?
    var trailerLink: String?
    var imageLink: String?
    var producerId: Int?
    var countries: [String]?
    
    required init?(map: Map) {
        
    }
    
    func mapping(map: Map) {
        id <- map["id"]
        name <- map["name"]
        year <- map["year"]
        rate <- map["rate"]
        trailerLink <- map["trailerLink"]
        imageLink <- map["imageLink"]
        producerId <- map["producerId"]
        countries <- map["country"]
    }
    
}

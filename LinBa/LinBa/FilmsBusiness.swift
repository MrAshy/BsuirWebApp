//
//  FavoriteBusiness.swift
//  LinBa
//
//  Created by Kirill Baranov on 05.03.17.
//  Copyright © 2017 Kirill Baranov. All rights reserved.
//

import UIKit
import RxSwift

class FilmsBusiness {
    
    func readFilms() -> Observable<[Film]?> {
        return ServerAPI.sharedInstance.getFilms()
    }
    
    func readFavoriteFilms() -> Observable<[Film]?> {
        return ServerAPI.sharedInstance.getFavoriteFilms()
    }
}

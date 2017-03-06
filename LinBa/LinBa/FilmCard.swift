//
//  FavoriteFilmCard.swift
//  LinBa
//
//  Created by Kirill Baranov on 05.03.17.
//  Copyright © 2017 Kirill Baranov. All rights reserved.
//

import UIKit

class FilmCard {

    var film: Film
    var producer: Producer
    
    init(film: Film, producer: Producer) {
        self.film = film
        self.producer = producer
    }
    
}

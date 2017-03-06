//
//  FilmCardsProtocol.swift
//  LinBa
//
//  Created by Kirill Baranov on 05.03.17.
//  Copyright © 2017 Kirill Baranov. All rights reserved.
//

import UIKit

protocol FilmCardsProtocol: BasePresenterProtocol {
    func setFilmCards(filmCards: [FilmCard])
}

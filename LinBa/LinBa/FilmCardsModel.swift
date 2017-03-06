//
//  FavoriteModel.swift
//  LinBa
//
//  Created by Kirill Baranov on 05.03.17.
//  Copyright © 2017 Kirill Baranov. All rights reserved.
//

import UIKit
import RxSwift

class FilmCardsModel {
    
    var filmsBusiness: FilmsBusiness
    var producerBusiness: ProducerBusiness
    
    init() {
        self.filmsBusiness = FilmsBusiness()
        self.producerBusiness = ProducerBusiness()
    }
    
    func getFilmCards() -> Observable<[FilmCard]?> {
        let filmsSource = filmsBusiness.readFilms()
        let producersSource = producerBusiness.readProducers()
        
        return Observable.zip(filmsSource, producersSource, resultSelector: {(films, producers) -> [FilmCard]? in
            return self.buildFilmCards(films: films, producers: producers)!
        })
    }
    
    func getFavoriteFilmCards() -> Observable<[FilmCard]?> {
        let favoriteFilmsSource = filmsBusiness.readFavoriteFilms()
        let producersSource = producerBusiness.readProducers()
        
        return Observable.zip(favoriteFilmsSource, producersSource, resultSelector: {(favoriteFilms, producers) -> [FilmCard]? in
            return self.buildFilmCards(films: favoriteFilms, producers: producers)!
        })
    }


    func buildFilmCards(films: [Film]?, producers: [Producer]?) -> [FilmCard]? {
        var filmCards = [FilmCard]()
        if let filmsItem = films {
            if let producersItem = producers {
                for filmItem in filmsItem {
                    let producer = producersItem.filter({ (producer) -> Bool in
                        return filmItem.producerId == producer.id
                    }).first
                    filmCards.append(FilmCard(film: filmItem, producer: producer!))
                }
            }
        }
        return filmCards
    }
}

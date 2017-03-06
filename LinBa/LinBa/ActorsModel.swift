//
//  ActorsModel.swift
//  LinBa
//
//  Created by Kirill Baranov on 07.03.17.
//  Copyright © 2017 Kirill Baranov. All rights reserved.
//

import UIKit
import RxSwift

class ActorsModel {

    func getActors(filmId: Int) -> Observable<[Actor]?> {
        return ServerAPI.sharedInstance.getActorsByFilmId(filmId: filmId)
    }
}

//
//  FilmCardsPresenter.swift
//  LinBa
//
//  Created by Kirill Baranov on 05.03.17.
//  Copyright © 2017 Kirill Baranov. All rights reserved.
//

import UIKit
import RxSwift

class FilmCardsPresenter {
    
    let disposeBag = DisposeBag()
    
    weak var filmCardsView: FilmCardsProtocol?
    private var filmCardsModel: FilmCardsModel
    
    init() {
        self.filmCardsModel = FilmCardsModel()
    }
    
    func attachView(view: FilmCardsProtocol) {
        filmCardsView = view
    }
    
    func getFilmCards() {
        filmCardsView?.showProgress()
        filmCardsModel.getFilmCards()
            .observeOn(MainScheduler())
            .subscribeOn(ConcurrentDispatchQueueScheduler(qos: .utility))
            .subscribe(onNext: { (filmCards) in
                self.filmCardsView?.setFilmCards(filmCards: filmCards!)
                self.filmCardsView?.hideProgress()
            }, onError: { (error) in
                print("\(error)")
            }, onCompleted: { 
                print("completed")
            }, onDisposed: { 
                print("disposed")
            }).addDisposableTo(disposeBag)
    }
    
    func getFavoriteFilmCards() {
        filmCardsView?.showProgress()
        filmCardsModel.getFavoriteFilmCards()
            .observeOn(MainScheduler())
            .subscribeOn(ConcurrentDispatchQueueScheduler(qos: .utility))
            .subscribe(onNext: { (filmCards) in
                self.filmCardsView?.setFilmCards(filmCards: filmCards!)
                self.filmCardsView?.hideProgress()
            }, onError: { (error) in
                print("\(error)")
            }, onCompleted: {
                print("completed")
            }, onDisposed: {
                print("disposed")
            }).addDisposableTo(disposeBag)
    }
    
}

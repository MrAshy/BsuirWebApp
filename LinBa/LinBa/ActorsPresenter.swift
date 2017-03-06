//
//  ActorsPresenter.swift
//  LinBa
//
//  Created by Kirill Baranov on 07.03.17.
//  Copyright © 2017 Kirill Baranov. All rights reserved.
//

import UIKit
import RxSwift

class ActorsPresenter {
    
    let disposeBag = DisposeBag()
    
    weak var actorsView: ActorsProtocol?
    private var actorsModel: ActorsModel
    
    init() {
        self.actorsModel = ActorsModel()
    }
    
    func attachView(view: ActorsProtocol) {
        self.actorsView = view
    }
    
    func getActors(filmId: Int) {
        actorsView?.showProgress()
        actorsModel.getActors(filmId: filmId)
            .observeOn(MainScheduler())
            .subscribeOn(ConcurrentDispatchQueueScheduler(qos: .utility))
            .subscribe(onNext: { (actors) in
                self.actorsView?.setActors(actors: actors!)
                self.actorsView?.hideProgress()
            }, onError: { (error) in
                print("\(error)")
            }, onCompleted: {
                print("completed")
            }, onDisposed: {
                print("disposed")
            }).addDisposableTo(disposeBag)
    }
    
}

//
//  FilmsViewController.swift
//  LinBa
//
//  Created by Kirill Baranov on 05.03.17.
//  Copyright © 2017 Kirill Baranov. All rights reserved.
//

import UIKit
import RxSwift

class FilmsViewController: UIViewController, FilmsTrailerDelegate {
    
    @IBOutlet weak var filmsTableView: UITableView!
    
    @IBOutlet weak var progress: UIActivityIndicatorView!
    
    let filmsCardsPresenter = FilmCardsPresenter()
    let filmCardsDataSource = FilmCardsDataSource()
    
    override func viewDidLoad() {
        super.viewDidLoad()
        filmCardsDataSource.observer = self 
        self.filmsTableView.dataSource = filmCardsDataSource
        self.filmsTableView.delegate = filmCardsDataSource
        self.filmCardsDataSource.filmCardDelegate = self
        
    }
    
    override func viewWillAppear(_ animated: Bool) {
        super.viewWillAppear(animated)
        filmsCardsPresenter.getFilmCards()
        filmsCardsPresenter.attachView(view: self)
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
    }
    
    func showTrailerView(url: String) {
        let vc = storyboard?.instantiateViewController(withIdentifier: "TrailerWebViewController") as! TrailerWebViewController
        vc.url = url
        self.navigationController?.pushViewController(vc, animated: false)
    }

}

extension FilmsViewController: FilmCardsProtocol {
    func showProgress() {
        progress.isHidden = false
        progress.startAnimating()
    }
    
    func hideProgress() {
        progress.isHidden = true
        progress.stopAnimating()
    }
    
    func setFilmCards(filmCards: [FilmCard]) {
        filmCardsDataSource.filmCards = filmCards
        self.filmsTableView.reloadData()
    }
}

extension FilmsViewController: FilmCardDelegate {
    
    func getFilmCard(filmCard: FilmCard) {
        ServerAPI.sharedInstance.addFilmToFavorites(filmId: filmCard.film.id!)
            .observeOn(MainScheduler())
            .subscribeOn(ConcurrentDispatchQueueScheduler(qos: .utility))
            .subscribe(onNext: { (message) in
                self.showAlert(message: message!, success: true, title: "SUCCESS")
            }, onError: { (error) in
                let err = error
                self.showAlert(message: err.localizedDescription, success: false, title: "FAILED")
            }).addDisposableTo(DisposeBag())
        
    }
    
    func showAlert(message: String, success: Bool, title: String) {
        let alert = UIAlertController(title: title, message: message, preferredStyle: .alert)
        if success {
            let okAction = UIAlertAction(title: "OK", style: .default) { (action) in
                self.navigationController?.popViewController(animated: true)
            }
            alert.addAction(okAction)
        }
        else {
            let cancelAction = UIAlertAction(title: "CANCEL", style: .cancel, handler: nil)
            alert.addAction(cancelAction)
        }
        self.present(alert, animated: true, completion: nil)
    }
    
}

//
//  FavouritesViewController.swift
//  LinBa
//
//  Created by Kirill Baranov on 02.03.17.
//  Copyright © 2017 Kirill Baranov. All rights reserved.
//

import UIKit
import RxSwift

class FavoritesViewController: UIViewController {

    @IBOutlet weak var favoritesTableView: UITableView!
    
    @IBOutlet weak var progress: UIActivityIndicatorView!
    
    let disposeBag = DisposeBag()
    
    let filmsCardsPresenter = FilmCardsPresenter()
    let favoriteFilmCardsDataSource = FavoriteFilmCardsDataSource()
    
    override func viewDidLoad() {
        super.viewDidLoad()
        self.favoritesTableView.estimatedRowHeight = 100.0
        self.favoritesTableView.rowHeight = UITableViewAutomaticDimension
        self.navigationController?.navigationBar.isHidden = false
        self.navigationItem.title = "Favorite"
        self.navigationItem.rightBarButtonItem = UIBarButtonItem(barButtonSystemItem: .add, target: self, action: #selector(FavoritesViewController.showFilmsViewController))
        self.navigationItem.leftBarButtonItem = UIBarButtonItem(title: "LogOut", style: .plain, target: self, action: #selector(FavoritesViewController.logOut))
        self.navigationController?.navigationBar.titleTextAttributes = [NSForegroundColorAttributeName: UIColor.white]
        self.navigationController?.navigationBar.tintColor = .white
        filmsCardsPresenter.attachView(view: self)
        self.favoritesTableView.dataSource = favoriteFilmCardsDataSource
        self.favoritesTableView.delegate = favoriteFilmCardsDataSource
        self.favoriteFilmCardsDataSource.favoriteFilmDelegate = self
        self.favoriteFilmCardsDataSource.observer = self
        
    }
    
    override func viewWillAppear(_ animated: Bool) {
        super.viewWillAppear(animated)
        filmsCardsPresenter.getFavoriteFilmCards()
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
    }
    
    
    func showFilmsViewController() {
        let vc = storyboard?.instantiateViewController(withIdentifier: "FilmsViewController") as! FilmsViewController
        self.navigationController?.pushViewController(vc, animated: true)
    }
    
    func logOut() {
        ServerAPI.sharedInstance.logOut()
            .observeOn(MainScheduler())
            .subscribeOn(ConcurrentDispatchQueueScheduler(qos: .utility))
            .subscribe(onNext: { (success) in
                if success {
                    self.navigationController?.popViewController(animated: true)
                }
            }, onError: { (error) in
                self.showAlert(message: error.localizedDescription, success: false, title: "FAILED")
            }).addDisposableTo(disposeBag)
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

extension FavoritesViewController: FilmCardsProtocol {
    func showProgress() {
        progress.isHidden = false
        progress.startAnimating()
    }
    
    func hideProgress() {
        progress.isHidden = true
        progress.stopAnimating()
    }
    
    func setFilmCards(filmCards: [FilmCard]) {
        favoriteFilmCardsDataSource.favoriteFilmCards = filmCards
        self.favoritesTableView.reloadData()
    }
}

extension FavoritesViewController: FavoriteFilmCellDelegate {
    
    func getFilmCardForDelete(filmCard: FilmCard) {
        ServerAPI.sharedInstance.deleteFilmFromFavorites(filmId: filmCard.film.id!)
            .observeOn(MainScheduler())
            .subscribeOn(ConcurrentDispatchQueueScheduler(qos: .utility))
            .subscribe(onNext: { (message) in
                //self.showAlert(message: message!, success: true, title: "SUCCESS")
                self.filmsCardsPresenter.getFavoriteFilmCards()
            }, onError: { (error) in
                let err = error
                self.showAlert(message: err.localizedDescription, success: false, title: "FAILED")
            }).addDisposableTo(disposeBag)
        
    }
    
    func getFilmCard(filmCard: FilmCard) {
        let vc = storyboard?.instantiateViewController(withIdentifier: "ActorsViewController") as! ActorsViewController
        vc.filmId = filmCard.film.id
        self.navigationController?.pushViewController(vc, animated: true)
    }
}

extension FavoritesViewController: RatingButtonDelegate {
    func getFilmIdForRate(filmId: Int) {
        let vc = storyboard?.instantiateViewController(withIdentifier: "RatingViewController") as! RatingViewController
        vc.filmId = filmId
        self.present(vc, animated: false, completion: nil)
    }
}

//
//  FavoriteFilmCardsDataSource.swift
//  LinBa
//
//  Created by Kirill Baranov on 06.03.17.
//  Copyright © 2017 Kirill Baranov. All rights reserved.
//

import UIKit

protocol FavoriteFilmCellDelegate: NSObjectProtocol {
    func getFilmCard(filmCard: FilmCard)
    func getFilmCardForDelete(filmCard: FilmCard)
}


class FavoriteFilmCardsDataSource: NSObject, UITableViewDataSource, UITableViewDelegate {
    
    var favoriteFilmCards: [FilmCard]
    var observer: RatingButtonDelegate?
    
    weak var favoriteFilmDelegate: FavoriteFilmCellDelegate?
    
    override init() {
        self.favoriteFilmCards = Array()
    }
    
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCell(withIdentifier: FavoriteTableViewCell.reuseIdentifier(), for: indexPath)
        cell.selectionStyle = .none
        let favoriteFilmCardsItem = favoriteFilmCards[indexPath.row]
        let favoriteFilmCardCell = cell as! FavoriteTableViewCell
        favoriteFilmCardCell.ivFavoriteFilm.kf.indicatorType = .activity
        favoriteFilmCardCell.setData(favoriteFilmCard: favoriteFilmCardsItem)
        favoriteFilmCardCell.delegate = observer
        favoriteFilmCardCell.filmId = favoriteFilmCardsItem.film.id
        cell.layoutIfNeeded()
        return cell
    }
    
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return favoriteFilmCards.count
    }
    
    func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
        if favoriteFilmDelegate != nil {
            self.favoriteFilmDelegate?.getFilmCard(filmCard: favoriteFilmCards[indexPath.row])
        }
    }
    
    func tableView(_ tableView: UITableView, canEditRowAt indexPath: IndexPath) -> Bool {
        return true
    }
    
    func tableView(_ tableView: UITableView, commit editingStyle: UITableViewCellEditingStyle, forRowAt indexPath: IndexPath) {
        if (editingStyle == .delete) {
            if favoriteFilmDelegate != nil {
                self.favoriteFilmDelegate?.getFilmCardForDelete(filmCard: favoriteFilmCards[indexPath.row])
            }
        }
    }
    
    
}

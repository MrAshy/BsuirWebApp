//
//  FilmCardsDataSource.swift
//  LinBa
//
//  Created by Kirill Baranov on 05.03.17.
//  Copyright © 2017 Kirill Baranov. All rights reserved.
//

import UIKit



class FilmCardsDataSource: NSObject, UITableViewDataSource, UITableViewDelegate {
    
    var filmCards: [FilmCard]
    var observer: FilmsTrailerDelegate?
    
    weak var filmCardDelegate: FilmCardDelegate?
    
    override init() {
        self.filmCards = Array()
    }
    
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCell(withIdentifier: FilmsTableViewCell.reuseIdentifier(), for: indexPath)
        cell.selectionStyle = .none
        let filmCardsItem = filmCards[indexPath.row]
        let filmCardCell = cell as! FilmsTableViewCell
        filmCardCell.ivFilm.kf.indicatorType = .activity
        filmCardCell.setData(filmCard: filmCardsItem)
        filmCardCell.delegate = observer
        return cell
    }
    
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return filmCards.count
    }
    
    func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
        
        if filmCardDelegate != nil {
            self.filmCardDelegate?.getFilmCard(filmCard: filmCards[indexPath.row])
        }
    }
    
}

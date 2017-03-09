//
//  FavoriteTableViewCell.swift
//  LinBa
//
//  Created by Kirill Baranov on 02.03.17.
//  Copyright © 2017 Kirill Baranov. All rights reserved.
//

import UIKit
import Kingfisher

protocol RatingButtonDelegate: NSObjectProtocol {
    func getFilmIdForRate(filmId: Int)
}



class FavoriteTableViewCell: UITableViewCell {

    @IBOutlet weak var ivFavoriteFilm: UIImageView!
    @IBOutlet weak var lFilmName: UILabel!
    @IBOutlet weak var lFilmRating: UILabel!
    @IBOutlet weak var lFilmProducer: UILabel!
    @IBOutlet weak var lFilmCountries: UILabel!
    @IBOutlet weak var bRate: UIButton!
    
    weak var delegate: RatingButtonDelegate?
    var filmId: Int? = nil
    
    
    override func awakeFromNib() {
        super.awakeFromNib()
        bRate.setRoundedBorder(withColor: UIColor(netHex: 0x2ED4C6))
        // Initialization code
    }
    
    static func reuseIdentifier() -> String {
        return "FavoriteTableViewCell"
    }

    override func setSelected(_ selected: Bool, animated: Bool) {
        super.setSelected(selected, animated: animated)

        // Configure the view for the selected state
    }
    
    
    @IBAction func showDetailInfo(_ sender: UIButton) {
    }
    
    func setData(favoriteFilmCard: FilmCard) {
        if let ivFilmItem = ivFavoriteFilm {
            let url = URL(string: favoriteFilmCard.film.imageLink!)
            ivFilmItem.kf.setImage(with: url, placeholder: nil, options: [.transition(ImageTransition.fade(1))], progressBlock: nil
                , completionHandler: nil)
        }
        if let lFilmNameItem = lFilmName {
            lFilmNameItem.text = favoriteFilmCard.film.name! + " (\(favoriteFilmCard.film.year!))"
        }
        if let lFilmRatingItem = lFilmRating {
            lFilmRatingItem.text = "rating: " + "\(favoriteFilmCard.film.rate!)"
            lFilmRatingItem.textColor = setRatingColor(rating: favoriteFilmCard.film.rate!)
        }
        if let lFilmProducerItem = lFilmProducer {
            lFilmProducerItem.text = "producer: " + "\(favoriteFilmCard.producer.name! + " " + favoriteFilmCard.producer.lastName!)"
        }
        if let lFilmCountriesItem = lFilmCountries {
            lFilmCountriesItem.text = favoriteFilmCard.film.countries?.joined(separator: ",")
        }
        
    }
    
    func setRatingColor(rating: Double) -> UIColor {
        var rColor: UIColor = .clear
        if rating < 5.0 {
            rColor = .red
        }
        if rating > 5.0 && rating < 7.0 {
            rColor = UIColor(netHex: 0xEBDF30)
        }
        if rating > 7.0 {
            rColor = .green
        }
        return rColor
    }
    
    @IBAction func addRateToFilm(_ sender: UIButton) {
        if delegate != nil {
            if let filmIdItem = filmId {
                self.delegate?.getFilmIdForRate(filmId: filmIdItem)
            }
        }
    }
    

}

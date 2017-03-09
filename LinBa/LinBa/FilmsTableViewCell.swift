//
//  FimsTableViewCell.swift
//  LinBa
//
//  Created by Kirill Baranov on 05.03.17.
//  Copyright © 2017 Kirill Baranov. All rights reserved.
//

import UIKit
import Kingfisher

protocol FilmsTrailerDelegate: NSObjectProtocol {
    func showTrailerView(url: String)
}

protocol FilmCardDelegate: NSObjectProtocol {
    func getFilmCard(filmCard: FilmCard)
}

class FilmsTableViewCell: UITableViewCell {
    
    @IBOutlet weak var ivFilm: UIImageView!
    @IBOutlet weak var lFilmName: UILabel!
    @IBOutlet weak var lFilmRating: UILabel!
    @IBOutlet weak var lFilmProducer: UILabel!
    @IBOutlet weak var lFilmCountries: UILabel!    
    @IBOutlet weak var bTrailer: UIButton!
    
    
    var url: String? = nil
    
    weak var delegate: FilmsTrailerDelegate?
    

    override func awakeFromNib() {
        super.awakeFromNib()
        bTrailer.setRoundedBorder(withColor: UIColor(netHex: 0x2ED4C6))
        // Initialization code
    }
    
    static func reuseIdentifier() -> String {
        return "FilmsTableViewCell"
    }

    override func setSelected(_ selected: Bool, animated: Bool) {
        super.setSelected(selected, animated: animated)

        // Configure the view for the selected state
    }
    
    @IBAction func showTriler(_ sender: UIButton) {
        if delegate != nil {
            self.delegate?.showTrailerView(url: url!)
        }
    }
    
    func setData(filmCard: FilmCard) {
        if let ivFilmItem = ivFilm {
            let url = URL(string: filmCard.film.imageLink!)
            ivFilmItem.kf.setImage(with: url, placeholder: nil, options: [.transition(ImageTransition.fade(1))], progressBlock: nil
            , completionHandler: nil)
        }
        if let lFilmNameItem = lFilmName {
            lFilmNameItem.text = filmCard.film.name! + " (\(filmCard.film.year!))"
        }
        if let lFilmRatingItem = lFilmRating {
            lFilmRatingItem.text = "rating: " + "\(filmCard.film.rate!)"
            lFilmRatingItem.textColor = setRatingColor(rating: filmCard.film.rate!)
        }
        if let lFilmProducerItem = lFilmProducer {
            lFilmProducerItem.text = "producer: " + "\(filmCard.producer.name! + " " + filmCard.producer.lastName!)"
        }
        if let lFilmCountriesItem = lFilmCountries {
            lFilmCountriesItem.text = filmCard.film.countries?.joined(separator: ",")
        }
        self.url = filmCard.film.trailerLink
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
    
    
    

}

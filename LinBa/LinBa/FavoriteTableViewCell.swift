//
//  FavoriteTableViewCell.swift
//  LinBa
//
//  Created by Kirill Baranov on 02.03.17.
//  Copyright © 2017 Kirill Baranov. All rights reserved.
//

import UIKit

class FavoriteTableViewCell: UITableViewCell {

    override func awakeFromNib() {
        super.awakeFromNib()
        // Initialization code
    }
    
    static func reuseIdentifier() -> String {
        return "FavoriteTableViewCell"
    }

    override func setSelected(_ selected: Bool, animated: Bool) {
        super.setSelected(selected, animated: animated)

        // Configure the view for the selected state
    }

}

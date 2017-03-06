//
//  ActorTableViewCell.swift
//  LinBa
//
//  Created by Kirill Baranov on 06.03.17.
//  Copyright © 2017 Kirill Baranov. All rights reserved.
//

import UIKit
import Kingfisher

class ActorTableViewCell: UITableViewCell {
    
    @IBOutlet weak var ivActor: UIImageView!
    
    @IBOutlet weak var lActorFullName: UILabel!

    override func awakeFromNib() {
        super.awakeFromNib()
        // Initialization code
    }
    
    static func reuseIdentifier() -> String {
        return "ActorTableViewCell"
    }

    override func setSelected(_ selected: Bool, animated: Bool) {
        super.setSelected(selected, animated: animated)

        // Configure the view for the selected state
    }
    
    func setData(actor: Actor) {
        if let ivActorItem = ivActor {
            let url = URL(string: actor.imageLink!)
            ivActorItem.kf.setImage(with: url, placeholder: nil, options: [.transition(ImageTransition.fade(1))], progressBlock: nil
                , completionHandler: nil)
        }
        if let lActorFullNameItem = lActorFullName {
            lActorFullNameItem.text = actor.name! + " " + actor.lastName!
        }
    }

}

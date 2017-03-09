//
//  UIButton.swift
//  LinBa
//
//  Created by Kirill Baranov on 08.03.17.
//  Copyright © 2017 Kirill Baranov. All rights reserved.
//

import UIKit

extension UIButton {
    
    func setRoundedBorder(withColor: UIColor) {
        self.backgroundColor = withColor
        self.layer.cornerRadius = 8
        self.layer.borderWidth = 1
        self.layer.borderColor = withColor.cgColor
    }
    
}

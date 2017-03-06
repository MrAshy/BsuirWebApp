//
//  ProducerBusiness.swift
//  LinBa
//
//  Created by Kirill Baranov on 05.03.17.
//  Copyright © 2017 Kirill Baranov. All rights reserved.
//

import UIKit
import RxSwift

class ProducerBusiness {
    
    func readProducers() -> Observable<[Producer]?> {
        return ServerAPI.sharedInstance.getProducers()
    }
    
    /*func readProducerByFilmsId(filmdId: Int) -> Observable<Producer?> {
        return ServerAPI.sharedInstance.get
    }*/
}

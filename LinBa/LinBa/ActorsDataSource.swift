//
//  ActorsDataSource.swift
//  LinBa
//
//  Created by Kirill Baranov on 07.03.17.
//  Copyright © 2017 Kirill Baranov. All rights reserved.
//

import UIKit


class ActorsDataSource: NSObject, UITableViewDelegate, UITableViewDataSource {
    
    var actors: [Actor]
    
    override init() {
        self.actors = Array()
    }
    
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCell(withIdentifier: ActorTableViewCell.reuseIdentifier(), for: indexPath)
        cell.selectionStyle = .none
        let actorItem = actors[indexPath.row]
        let actorCell = cell as! ActorTableViewCell
        actorCell.ivActor.kf.indicatorType = .activity
        actorCell.setData(actor: actorItem)
        return cell
    }
    
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return actors.count
    }
    
}

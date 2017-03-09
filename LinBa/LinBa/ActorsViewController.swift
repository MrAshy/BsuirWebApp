//
//  ActorsViewController.swift
//  LinBa
//
//  Created by Kirill Baranov on 06.03.17.
//  Copyright © 2017 Kirill Baranov. All rights reserved.
//

import UIKit

class ActorsViewController: UIViewController {

    @IBOutlet weak var progress: UIActivityIndicatorView!
    
    @IBOutlet weak var actorTableView: UITableView!
    
    let actorsPresenter = ActorsPresenter()
    let actorsDataSource = ActorsDataSource()
    
    var filmId: Int? = nil
    
    override func viewDidLoad() {
        super.viewDidLoad()
        self.navigationItem.title = "Actors"
        self.navigationController?.navigationBar.titleTextAttributes = [NSForegroundColorAttributeName: UIColor.white]
        self.navigationController?.navigationBar.tintColor = .white
        self.actorTableView.dataSource = actorsDataSource
        self.actorTableView.delegate = actorsDataSource

        // Do any additional setup after loading the view.
    }
    
    override func viewWillAppear(_ animated: Bool) {
        super.viewWillAppear(animated)
        actorsPresenter.getActors(filmId: filmId!)
        actorsPresenter.attachView(view: self)
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    

    /*
    // MARK: - Navigation

    // In a storyboard-based application, you will often want to do a little preparation before navigation
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        // Get the new view controller using segue.destinationViewController.
        // Pass the selected object to the new view controller.
    }
    */

}

extension ActorsViewController: ActorsProtocol {
    
    func showProgress() {
        self.progress.isHidden = false
        self.progress.startAnimating()
    }
    
    func hideProgress() {
        self.progress.isHidden = true
        self.progress.stopAnimating()
    }
    
    func setActors(actors: [Actor]) {
        self.actorsDataSource.actors = actors
        self.actorTableView.reloadData()
    }
}

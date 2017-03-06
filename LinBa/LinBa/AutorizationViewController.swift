//
//  AutorizationViewController.swift
//  LinBa
//
//  Created by Kirill Baranov on 13.02.17.
//  Copyright © 2017 Kirill Baranov. All rights reserved.
//

import UIKit
import RxSwift

class AvtorizationViewController: UIViewController {
    
    @IBOutlet weak var tfFullName: UITextField!
    @IBOutlet weak var tfPassword: UITextField!
    
    let disposeBag = DisposeBag()
    
    override func viewDidLoad() {
        super.viewDidLoad()
        self.navigationController?.navigationBar.isHidden = true
    }
    
    override func viewDidAppear(_ animated: Bool) {
        super.viewDidAppear(animated)
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
    }
    
    @IBAction func enterSignUp(_ sender: UIButton) {
    }
    
    @IBAction func enterSignIn(_ sender: UIButton) {
         (ServerAPI.sharedInstance.logIn(fullName: tfFullName.text!, password: tfPassword.text!))
            .observeOn(MainScheduler())
            .subscribeOn(ConcurrentDispatchQueueScheduler(qos: .utility))
            .subscribe(onNext: { (success) in
            if success {
                let vc = self.storyboard?.instantiateViewController(withIdentifier: "FavoritesViewController") as! FavoritesViewController
                self.navigationController?.pushViewController(vc, animated: false)
            }
         }, onError: {(error) in
            let err = error as! APIError
            self.showAlert(message: err.desc)
         }).addDisposableTo(disposeBag)
    }
    
    func showAlert(message: String) {
        let alert = UIAlertController(title: title, message: message, preferredStyle: .alert)
        let cancelAction = UIAlertAction(title: "CANCEL", style: .cancel, handler: nil)
            alert.addAction(cancelAction)
        self.present(alert, animated: true, completion: nil)
    }
    
}

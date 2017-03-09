//
//  AutorizationViewController.swift
//  LinBa
//
//  Created by Kirill Baranov on 13.02.17.
//  Copyright © 2017 Kirill Baranov. All rights reserved.
//

import UIKit
import RxSwift

class AvtorizationViewController: UIViewController, UITextFieldDelegate {
    
    @IBOutlet weak var tfFullName: UITextField!
    @IBOutlet weak var tfPassword: UITextField!
    @IBOutlet weak var progress: UIActivityIndicatorView!
    
    @IBOutlet weak var bSignUp: UIButton!
    @IBOutlet weak var bSignIn: UIButton!
    
    
    let disposeBag = DisposeBag()
    
    override func viewDidLoad() {
        super.viewDidLoad()
        bSignUp.setRoundedBorder(withColor: UIColor(netHex: 0x5E5E5E))
        bSignIn.setRoundedBorder(withColor: UIColor(netHex: 0x5E5E5E))
        tfFullName.text = "test"
        tfPassword.text = "test"
        self.navigationController?.navigationBar.isHidden = true
        tfFullName.delegate = self
        tfPassword.delegate = self
        self.progress.isHidden = true
    }
    
    func textFieldShouldReturn(_ textField: UITextField) -> Bool {
        textField.resignFirstResponder()
        return true
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
        self.progress.startAnimating()
        self.progress.isHidden = false
        (ServerAPI.sharedInstance.logIn(fullName: tfFullName.text!, password: tfPassword.text!))
            .observeOn(MainScheduler())
            .subscribeOn(ConcurrentDispatchQueueScheduler(qos: .utility))
            .subscribe(onNext: { (success) in
            self.progress.stopAnimating()
            self.progress.isHidden = true
            if success {
                let vc = self.storyboard?.instantiateViewController(withIdentifier: "FavoritesViewController") as! FavoritesViewController
                self.navigationController?.pushViewController(vc, animated: false)
            }
        }, onError: {(error) in
            self.progress.stopAnimating()
            self.progress.isHidden = true
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

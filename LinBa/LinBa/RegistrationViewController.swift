//
//  RegistrationViewController.swift
//  LinBa
//
//  Created by Kirill Baranov on 13.02.17.
//  Copyright © 2017 Kirill Baranov. All rights reserved.
//

import UIKit
import RxSwift

class RegistrationViewController: UIViewController, UITextFieldDelegate {

    
    @IBOutlet weak var tfFullname: UITextField!
    @IBOutlet weak var tfPassword: UITextField!
    
    @IBOutlet weak var bSignUp: UIButton!
    @IBOutlet weak var bCancel: UIButton!
    
    let disposeBag = DisposeBag()
    
    override func viewDidLoad() {
        super.viewDidLoad()
        bSignUp.setRoundedBorder(withColor: UIColor(netHex: 0x5E5E5E))
        bCancel.setRoundedBorder(withColor: UIColor(netHex: 0x5E5E5E))
        self.navigationController?.navigationBar.isHidden = true
        self.tfFullname.delegate = self
        self.tfPassword.delegate = self
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
        ServerAPI.sharedInstance.createUser(fullName: tfFullname.text!, password: tfPassword.text!)
            .observeOn(MainScheduler())
            .subscribeOn(ConcurrentDispatchQueueScheduler(qos: .utility))
            .subscribe(onNext: { (message) in
            self.showAlert(message: message!, success: true, title: "Success")
        }, onError: {(error) in
            if error is APIError {
                let err = error as! APIError
                self.showAlert(message: err.desc, success: false, title: "FAILED")
            }
            else {
                self.showAlert(message: error.localizedDescription, success: false, title: "FAILED")
            }
        }).addDisposableTo(disposeBag)
        
    }
    
    func showAlert(message: String, success: Bool, title: String) {
        let alert = UIAlertController(title: title, message: message, preferredStyle: .alert)
        if success {
            let okAction = UIAlertAction(title: "OK", style: .default) { (action) in
                self.navigationController?.popViewController(animated: true)
            }
            alert.addAction(okAction)
        }
        else {
            let cancelAction = UIAlertAction(title: "CANCEL", style: .cancel, handler: nil)
            alert.addAction(cancelAction)
        }
        self.present(alert, animated: true, completion: nil)
    }
        
    
    
    @IBAction func enterCancel(_ sender: UIButton) {
    }
    
}

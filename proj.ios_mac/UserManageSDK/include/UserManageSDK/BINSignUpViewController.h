//
//  BINSignUpViewController.h
//  UserManage
//
//  Created by bin on 15/6/26.
//  Copyright (c) 2015年 bin. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface BINSignUpViewController : UIViewController<UIAlertViewDelegate>
@property (weak, nonatomic) IBOutlet UITextField *usernameTextField;
@property (weak, nonatomic) IBOutlet UITextField *nameTextField;
@property (weak, nonatomic) IBOutlet UITextField *passwordTextField;
@property (weak, nonatomic) IBOutlet UIButton *signupButton;
- (IBAction)signpButtonPressed:(UIButton *)sender;
- (IBAction)usernameEditingChanged:(UITextField *)sender;
- (IBAction)nameEditingChanged:(UITextField *)sender;

- (IBAction)passwordEditingChanged:(UITextField *)sender;
@end

from typing import Tuple
from flask import Flask, render_template, redirect, url_for
from flask_bootstrap import Bootstrap
from flask_wtf import FlaskForm
from wtforms import StringField, FloatField, SubmitField
from wtforms.validators import DataRequired

import StatsPythonPyBind as Stats

app = Flask(__name__)
app.config["DEBUG"] = True

# Flask-WTF requires an encryption key - the string can be anything
app.config['SECRET_KEY'] = 'C2HWGVoGHfNYBsrYQg8EcMrdTimkZfAb'

# Flask-Bootstrap requires this line
Bootstrap(app)


class TTestForm(FlaskForm):
    mu0 =  FloatField('mu0', validators=[DataRequired()])
    x_bar =  FloatField('x-bar', validators=[DataRequired()])
    sx =  FloatField('sx', validators=[DataRequired()])
    N =  FloatField('N', validators=[DataRequired()])
    submit = SubmitField('Submit')


@app.route('/', methods=['GET', 'POST'])
def index():
    form = TTestForm()
    message = ""
    if form.validate_on_submit():
        mu0 = form.mu0.data
        xbar = form.x_bar.data
        sx = form.sx.data
        n = form.N.data
        return redirect( url_for('ttest', mu0=mu0, xbar=xbar, sx=sx, n=n) )
    return render_template('index.html', form=form, message=message)


@app.route('/ttest/<float:mu0>/<float:xbar>/<float:sx>/<float:n>')
def ttest(mu0: float, xbar: float, sx: float, n: float):
    results: dict = Stats.SummaryDataTTest(mu0, xbar, sx, n)
    return render_template('ttest.html', results=results)


if __name__ == "__main__":
    app.run(debug=True)
